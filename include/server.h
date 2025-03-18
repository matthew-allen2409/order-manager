#include <list>
#include <mutex>

#include "FIX_message.h"

#ifndef SERVER_H
#define SERVER_H

class Server {
   public:
    Server();
    ~Server();

    int server_socket;

    void begin();

   private:
    std::mutex client_mutex;
    std::list<int> clients;
    bool running = true;

    void handle_client(int clientSocket);
    void forward_order(const FIXMessage &message);
};

#endif
