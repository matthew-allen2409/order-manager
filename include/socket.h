#ifndef SOCKET_H
#define SOCKET_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>

class Socket {
public:
    Socket();
    ~Socket();

    bool create_socket(int domain, int type, int protocol);

    bool bind_socket(const sockaddr_in& address);

    int get_fd() const;

private:
    int sockfd;
};

#endif
