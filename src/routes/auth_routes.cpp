
    #include <crow.h>
    #include <nlohmann/json.hpp>
    #include "routes/auth_routes.hpp"
    #include "services/user_service.hpp"
    #include "services/jwt_service.hpp"
    #include "utils/crypto_utils.hpp"
    #include "utils/validation_utils.hpp"

    using json = nlohmann::json;

    void register_auth_routes(crow::SimpleApp& app, UserService& users, JwtService& jwt) {
        CROW_ROUTE(app, "/register").methods("POST"_method)([&](const crow::request& req){
            try {
                auto body = json::parse(req.body);
                std::string username = body.value("username", "");
                std::string password = body.value("password", "");

                if (!valid_username(username)) {
                    return crow::response(400, R\"({\"error\":\"invalid_username\"})\"");
                }
                if (!strong_password(password)) {
                    return crow::response(400, R\"({\"error\":\"weak_password\"})\")");
                }
                if (users.find_user(username)) {
                    return crow::response(409, R\"({\"error\":\"user_exists\"})\")");
                }

                std::vector<unsigned char> salt, hash;
                if (!pbkdf2_hash(password, salt, hash)) {
                    return crow::response(500, R\"({\"error\":\"hash_failure\"})\")");
                }
                if (!users.add_user(username, hex_encode(salt), hex_encode(hash))) {
                    return crow::response(500, R\"({\"error\":\"save_failure\"})\")");
                }
                return crow::response(201, R\"({\"status\":\"ok\"})\")");
            } catch(...) {
                return crow::response(400, R\"({\"error\":\"bad_request\"})\")");
            }
        });

        CROW_ROUTE(app, "/login").methods("POST"_method)([&](const crow::request& req){
            try {
                auto body = json::parse(req.body);
                std::string username = body.value("username", "");
                std::string password = body.value("password", "");

                if (!valid_username(username) || password.empty()) {
                    return crow::response(400, R\"({\"error\":\"invalid_credentials\"})\")0");
                }
                User* found = users.find_user(username);
                if (!found) return crow::response(401, R\"({\"error\":\"invalid_credentials\"})\")");

                auto salt = hex_decode(found->salt_hex);
                auto expected = hex_decode(found->hash_hex);
                if (!pbkdf2_verify(password, salt, expected)) {
                    return crow::response(401, R\"({\"error\":\"invalid_credentials\"})\")");
                }

                auto token = jwt.make_jwt(username, 3600);
                json resp; resp[\"token\""] = token;
                return crow::response(200, resp.dump());
            } catch(...) {
                return crow::response(400, R\"({\"error\":\"bad_request\"})\")");
            }
        });
    }