#include <sstream>

#include "Utils.h"

Utils::UniquePtr<BIO> Utils::operator|(Utils::UniquePtr<BIO> lower, Utils::UniquePtr<BIO> upper) {
    BIO_push(upper.get(), lower.release());
    return upper;
}

std::vector<std::string> Utils::parseResponse(const std::string &response) {
    std::istringstream ss(response);
    std::string token;
    std::vector<std::string> tokens;
    while (getline(ss, token, ':')) {
        tokens.push_back(token);
    }
    return tokens;
}

