#pragma once
#include <string>

struct User {
    std::string username;
    std::string salt_hex;
    std::string hash_hex;
};
