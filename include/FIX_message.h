#ifndef FIX_MESSAGE_H
#define FIX_MESSAGE_H

#include <string>
#include <unordered_map>
#include <tuple>
#include <vector>

class FIXMessage {
public:
    FIXMessage(std::string string);
    std::string serialize() const noexcept;

    std::unordered_map<std::string, std::string> tag_map;
    std::vector<std::tuple<std::string, std::string>> tags;
};

#endif
