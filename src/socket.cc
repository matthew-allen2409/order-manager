#include "socket.h"

Socket::Socket() : sockfd(-1) {}
Socket::~Socket() {
    if (sockfd != -1) {
        close(sockfd);
    }
}

bool Socket::create_socket(int domain, int type, int protocol) {
    sockfd = socket(domain, type, protocol);
    if (sockfd == -1) {
        perror("Socket creation failed");
        return false;
    }
    return true;
}

bool Socket::bind_socket(const sockaddr_in& address) {
    if (bind(sockfd, reinterpret_cast<const sockaddr*>(&address), sizeof(address)) == -1) {
        perror("Socket binding failed");
        return false;
    }
    return true;
}

int Socket::get_fd() const { return sockfd; }
