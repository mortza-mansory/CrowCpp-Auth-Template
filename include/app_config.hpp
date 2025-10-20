#pragma once
#include <string>

inline std::string getenv_or(const std::string& k, const std::string& def="") {
    const char* v = std::getenv(k.c_str());
    if (!v) return def;
    return std::string(v);
}
