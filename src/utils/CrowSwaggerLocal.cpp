#include "CrowSwaggerLocal.hpp"
#include <fstream>
#include <sstream>

CrowSwaggerLocal::CrowSwaggerLocal(const std::string& ui_path)
    : swagger_ui_path(ui_path)
{
    swagger["openapi"] = "3.0.0";
    swagger["info"]["title"] = "My Crow API";
    swagger["info"]["version"] = "1.0.0";
    swagger["paths"] = nlohmann::json::object();
}

void CrowSwaggerLocal::addRoute(const std::string& path, const std::string& method, const std::string& description) {
    swagger["paths"][path][method]["description"] = description;
}

void CrowSwaggerLocal::registerRoutes(crow::SimpleApp& app) {
    app.route_dynamic("/swagger.json", [this](){
        return crow::response(swagger.dump());
    });

    app.route_dynamic("/docs/<string>")( [this](std::string file) {
        std::ifstream ifs(swagger_ui_path + "/" + file, std::ios::binary);
        if (!ifs.is_open()) return crow::response(404);
        std::ostringstream buf;
        buf << ifs.rdbuf();
        return crow::response(buf.str());
    });

    app.route_dynamic("/docs")([this](){
        std::ifstream ifs(swagger_ui_path + "/index.html", std::ios::binary);
        if (!ifs.is_open()) return crow::response(404);
        std::ostringstream buf;
        buf << ifs.rdbuf();
        return crow::response(buf.str());
    });
}
