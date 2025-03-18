#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H

#include "socket.h"

#include <memory>
#include <mutex>
#include <vector>

class SocketManager {
public:
    bool addSocket(std::shared_ptr<Socket> socket);

    std::shared_ptr<Socket> getSocket(size_t index);

    void closeAllSockets();

private:
    std::vector<std::shared_ptr<Socket>> sockets;
    std::mutex mtx;
};

#endif
