#include <crow.h>
#include "app_config.hpp"
#include "services/jwt_service.hpp"
#include "services/user_service.hpp"
#include "routes/auth_routes.hpp"
#include "routes/profile_routes.hpp"
#include "utils/CrowSwaggerLocal.hpp" 

int main(int argc, char** argv) {
    crow::SimpleApp app;
    std::string jwt_secret = getenv_or("JWT_SECRET", "dev_secret_change_me");
    JwtService jwt(jwt_secret);
    UserService users("users.json");

    register_auth_routes(app, users, jwt);
    register_profile_routes(app, users, jwt);

    CrowSwaggerLocal swagger("dist/swagger-ui");
    swagger.addRoute("/auth/login", "post", "User login");
    swagger.addRoute("/profile/me", "get", "Get user profile");
    swagger.registerRoutes(app);

    int port = std::stoi(getenv_or("PORT", "8080"));
    app.port(port).multithreaded().run();
    return 0;
}
