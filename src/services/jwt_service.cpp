
    #include "services/jwt_service.hpp"
    #include <jwt-cpp/jwt.h>
    #include <chrono>

    JwtService::JwtService(const std::string& secret): secret_(secret) {}

    std::string JwtService::make_jwt(const std::string& username, int expire_seconds) {
        auto token = jwt::create()
            .set_issuer("crow-auth-demo")
            .set_type("JWS")
            .set_payload_claim("user", jwt::claim(username))
            .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{expire_seconds})
            .sign(jwt::algorithm::hs256{secret_});
        return token;
    }

    bool JwtService::verify_jwt(const std::string& token, std::string& out_username) {
        try {
            auto decoded = jwt::decode(token);
            auto verifier = jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256{secret_})
                .with_issuer("crow-auth-demo");
            verifier.verify(decoded);
            if (decoded.has_payload_claim("user")) {
                out_username = decoded.get_payload_claim("user").as_string();
                return true;
            }
        } catch (...) {
            return false;
        }
        return false;
    }
