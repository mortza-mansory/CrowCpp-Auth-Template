#pragma once
#include <crow.h>

void register_auth_routes(crow::SimpleApp& app, class UserService& users, class JwtService& jwt);
