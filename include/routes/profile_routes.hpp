#pragma once
#include <crow.h>

void register_profile_routes(crow::SimpleApp& app, class UserService& users, class JwtService& jwt);
