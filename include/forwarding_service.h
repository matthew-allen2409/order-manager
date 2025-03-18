#ifndef FORWARDING_SERVICE_H
#define FORWARDING_SERVICE_H

#include <queue>

#include "FIX_message.h"

class ForwardingService {
    public:
        void forward_message(FIXMessage &message);

    private:
        std::queue<FIXMessage> toBeForwarded;
};

#endif
