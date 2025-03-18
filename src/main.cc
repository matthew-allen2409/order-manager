#include <iostream>
#include "server.h"

int main() {
    try {
        Server server;

        server.begin();
    } catch (std::string err) {
        std::cerr << err << std::endl;
        return 1;
    }


}
