#pragma once
#include <string>

class JwtService {
public:
    JwtService(const std::string& secret);
    std::string make_jwt(const std::string& username, int expire_seconds = 3600);
    bool verify_jwt(const std::string& token, std::string& out_username);
private:
    std::string secret_;
};
