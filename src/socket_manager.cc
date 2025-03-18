#include "socket_manager.h"

bool SocketManager::addSocket(std::shared_ptr<Socket> socket) {
    std::lock_guard<std::mutex> lock(mtx);
    sockets.push_back(socket);
    return true;
}

std::shared_ptr<Socket> SocketManager::getSocket(size_t index) {
    std::lock_guard<std::mutex> lock(mtx);
    if (index < sockets.size()) {
        return sockets[index];
    }
    return nullptr;
}

void SocketManager::closeAllSockets() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& socket : sockets) {
        socket.reset();
    }
    sockets.clear();
}
