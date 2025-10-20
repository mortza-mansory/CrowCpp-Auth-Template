#pragma once
#include <string>
#include <vector>
#include "../models/user.hpp"

class UserService {
public:
    UserService(const std::string& users_path = "users.json");
    std::vector<User> list_users() const;
    bool save_users() const;
    bool add_user(const std::string& username, const std::string& salt_hex, const std::string& hash_hex);
    User* find_user(const std::string& username);
private:
    std::string path_;
    mutable std::vector<User> users_;
};
