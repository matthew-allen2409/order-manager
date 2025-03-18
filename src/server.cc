#include <functional>
#include <iostream>
#include <cstring>
#include <string>
#include <mutex>
#include <cstdio>
#include <algorithm>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "server.h"
#include "FIX_message.h"
#include "string_utils.h"

using std::string;

Server::Server() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        throw std::string("Socket creation failed");
    }
    this->server_socket = sockfd;

    struct sockaddr_in address;
    address.sin_family      = AF_INET;
    address.sin_port        = htons(8081);
    address.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address))) {
        close(sockfd);
        throw std::string("failed to bind socket");
    }

    if (listen(sockfd, 50)) {
        close(sockfd);
        throw std::string("failed to listen");
    }
}

Server::~Server() {
    close(this->server_socket);
    std::lock_guard lock(client_mutex);
    for (auto socket : clients) {
        close(socket);
    }
}

void Server::begin() {
    while (this->running) {
        int clientSocket = accept(this->server_socket, nullptr, nullptr);
        if (clientSocket < 0) {
            perror("failed to accept connection");
            continue;
        }

        std::thread thread(std::bind(&Server::handle_client, this, clientSocket));
        thread.detach();
        std::lock_guard lock(this->client_mutex);
        this->clients.push_back(clientSocket);
    }
}

void Server::handle_client(int clientSocket) {
    char buffer[1024] = {0};
    while (int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) {
        if (bytesRead < 0) {
            perror("failed to read");
            close(clientSocket);
            return;
        }

        stripWhitespace(buffer);

        if (std::strcmp(buffer, "END") == 0) {
            break;
        }

        try {
            const FIXMessage msg(buffer);

            forward_order(msg);
        } catch (std::string str) {
            send(clientSocket, str.c_str(), str.size(), 0);
            break;
        }

        memset(buffer, 0, sizeof(buffer));
    }

    std::cout << "closing connection" << std::endl;
    std::lock_guard lock(this->client_mutex);
    close(clientSocket);
    auto it = std::find(this->clients.begin(), this->clients.end(), clientSocket);

    if (it != this->clients.end()) {
        this->clients.erase(it);
    }
}

void Server::forward_order(const FIXMessage &message) {
    std::lock_guard lock(client_mutex);

    for (auto client:clients) {
        std::string messageStr = message.serialize();
        send(client, messageStr.c_str(), messageStr.size(), 0);
    }
}
