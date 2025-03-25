#ifndef FIX_MESSAGE_H
#define FIX_MESSAGE_H

#include <string>
#include <unordered_map>
#include <tuple>
#include <vector>

static const int MAX_PRICE = 1'000'000;
static const int MAX_QUANTITY = 1'000'000;

class FIXMessage {
public:
    FIXMessage(std::string string);
    std::string serialize() const noexcept;

    std::unordered_map<std::string, std::string> tag_map;
    std::vector<std::tuple<std::string, std::string>> tags;
};

#endif
