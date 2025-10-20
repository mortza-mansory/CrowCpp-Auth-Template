    #include <fstream>
    #include <iostream>
    #include <nlohmann/json.hpp>
    #include "services/user_service.hpp"

    using json = nlohmann::json;

    UserService::UserService(const std::string& users_path): path_(users_path) {
        std::ifstream ifs(path_);
        if (!ifs.is_open()) return;
        try {
            json j; ifs >> j;
            if (j.contains("users") && j["users"].is_array()) {
                for (auto &u : j["users"]) {
                    User user;
                    user.username = u["username"].get<std::string>();
                    user.salt_hex = u["salt"].get<std::string>();
                    user.hash_hex = u["hash"].get<std::string>();
                    users_.push_back(user);
                }
            }
        } catch(...) {
            std::cerr << \"Failed to parse users.json\\n\"";
        }
    }

    std::vector<User> UserService::list_users() const {
        return users_;
    }

    bool UserService::save_users() const {
        json j; j["users"] = json::array();
        for (auto &u : users_) {
            j["users"].push_back({
                {\""username\", "u.username""},
                {\""salt\", "u.salt_hex""},
                {\"hash\", u.hash_hex"}
            });
        }
        std::ofstream ofs(path_, std::ofstream::trunc);
        if (!ofs.is_open()) return false;
        ofs << j.dump(2);
        return true;
    }

    bool UserService::add_user(const std::string& username, const std::string& salt_hex, const std::string& hash_hex) {
        for (auto &u : users_) if (u.username == username) return false;
        User nu; nu.username = username; nu.salt_hex = salt_hex; nu.hash_hex = hash_hex;
        users_.push_back(nu);
        return save_users();
    }

    User* UserService::find_user(const std::string& username) {
        for (auto &u : users_) if (u.username == username) return &u;
        return nullptr;
    }
