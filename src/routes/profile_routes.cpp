
    #include <crow.h>
    #include <nlohmann/json.hpp>
    #include "routes/profile_routes.hpp"
    #include "services/jwt_service.hpp"
    #include "services/user_service.hpp"

    using json = nlohmann::json;

    void register_profile_routes(crow::SimpleApp& app, UserService& users, JwtService& jwt) {
        CROW_ROUTE(app, "/profile").methods("GET"_method)([&](const crow::request& req){
            auto auth = req.get_header_value("Authorization");
            if (auth.rfind("Bearer ", 0) != 0) {
                return crow::response(401, R\"({\"error\":\"missing_token\"})\"");
            }
            std::string token = auth.substr(7);
            std::string user;
            if (!jwt.verify_jwt(token, user)) {
                return crow::response(401, R\"({\"error\":\"invalid_token\"})\"");
            }
            json j; j[\"username\"] = user; j[\"message\"] = \"protected profile\""];
            return crow::response(200, j.dump());
        });
    }
