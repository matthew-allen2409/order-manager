#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include <tuple>
#include "FIX_message.h"
#include "string_utils.h"

const char DELIMETER = 0x01;

std::vector<std::string> splitBySOH(const std::string& message) {
    std::vector<std::string> tokens;
    size_t                   start = 0;
    size_t                   end;

    while ((end = message.find(DELIMETER, start)) != std::string::npos) {
        tokens.push_back(message.substr(start, end - start));
        start = end + 1;
    }

    return tokens;
}

std::tuple<std::string, std::string> parseTagValue(std::string& tagValue) {
    size_t      pos   = tagValue.find("=");
    std::string tag   = tagValue.substr(0, pos);
    std::string value = tagValue.substr(pos + 1);

    return std::tuple(tag, value);
}

bool isValidTagValue(std::string& tagValue) {
    size_t pos = tagValue.find("=");
    if (pos == std::string::npos) {
        std::cerr << "tag-value pair missing = delimeter" << std::endl;
        return false;
    }

    auto tagValuePair = parseTagValue(tagValue);

    std::string tag   = std::get<0>(tagValuePair);
    std::string value = std::get<1>(tagValuePair);

    for (char ch : tag) {
        if (!std::isdigit(ch)) {
            std::cerr << "tag is not numeric" << std::endl;
            return false;
        }
    }

    return true;
}

bool isValidFIXMessage(std::string& input) {
    if (input.back() != 0x01) {
        std::cerr << "FIX message must end with a <SOH> character" << std::endl;
        return false;
    }

    auto tokens = splitBySOH(input);

    for (auto token : tokens) {
        if (!isValidTagValue(token)) {
            return false;
        }
    }

    auto versionPair = parseTagValue(tokens[0]);

    if (!(std::get<0>(versionPair) == "8")) {
        std::cerr << "First tag must be for FIX version" << std::endl;
        return false;
    }

    auto lengthPair = parseTagValue(tokens[1]);
    if (!(std::get<0>(lengthPair) == "9")) {
        std::cerr << "Second tag must be message length" << std::endl;
        return false;
    }

    auto messageTypePair = parseTagValue(tokens[2]);
    if (!(std::get<0>(messageTypePair) == "35")) {
        std::cerr << "Third tag must be message type" << std::endl;
        return false;
    }

    return true;
}

FIXMessage::FIXMessage(std::string string) {
    if (!isValidFIXMessage(string)) {
        throw std::string("Error: Invalid FIX Message");
    }

    auto tokens = splitBySOH(string);

    for (auto token : tokens) {
        std::cout << token << std::endl;

        auto        tagValue = parseTagValue(token);
        std::string key      = std::get<0>(tagValue);
        std::string value    = std::get<1>(tagValue);

        this->tag_map[key] = value;
        this->tags.push_back(std::tuple(key, value));
    }

    std::string orderType = tag_map["40"];
    if (orderType != "1" && orderType != "2") {
        throw "Invalid Order type";
    }

    std::string price = tag_map["44"];
    if(!isNumeric(price) || stoi(price) < 1 || stoi(price) > MAX_PRICE) {
        throw "Invalid price";
    }

    std::string quantity = tag_map["38"];
    if(!isNumeric(quantity) || stoi(quantity) < 1 || stoi(quantity) > MAX_PRICE) {
        throw "Invalid price";
    }
}

std::string FIXMessage::serialize() const noexcept {
    std::ostringstream oss;

    for (auto [key, value]:tags) {
        oss << key << '=' << value << '\x01';
    }

    return oss.str();
}
