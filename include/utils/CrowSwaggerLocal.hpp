#pragma once
#include "crow_all.h"
#include <nlohmann/json.hpp>
#include <string>

class CrowSwaggerLocal {
public:
    CrowSwaggerLocal(const std::string& ui_path);

    void addRoute(const std::string& path, const std::string& method, const std::string& description);
    void registerRoutes(crow::SimpleApp& app);

private:
    nlohmann::json swagger;
    std::string swagger_ui_path;
};
