#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <iostream>

const char* FIX_MESSAGE = "8=MATT.HEW""\x01""9=251""\x01""35=D""\x01""49=AFUNDMGR""\x01""56=ABROKER""\x01""34=2""\x01""52=2003061501:14:49""\x01""11=12345""\x01""1=111111""\x01""63=0""\x01""64=20030621""\x01""21=3""\x01""110=1000""\x01""111=50000""\x01""55=IBM""\x01""48=459200101""\x01""22=1""\x01""54=1""\x01""60=2003061501:14:49""\x01""38=5000""\x01""40=1""\x01""44=15.75""\x01""15=USD""\x01""59=0""\x01""10=127""\x01";

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Failed to create socket");
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8081);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Failed to connect");
        close(clientSocket);
        return 1;
    }
    send(clientSocket, FIX_MESSAGE, strlen(FIX_MESSAGE), 0);

    char buffer[1024] = {0};

    while (recv(clientSocket, buffer, sizeof(buffer), 0)) {
        std::cout << "received" << std::endl;
        std::cout << buffer << std::endl;
    }

    close(clientSocket);
    return 0;
}

