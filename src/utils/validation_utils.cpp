
    #include <regex>
    #include <cctype>
    #include "utils/validation_utils.hpp"

    bool valid_username(const std::string& u) {
        std::regex re(\"^[A-Za-z0-9_\\-]{3,32}$\"");
        return std::regex_match(u, re);
    }

    bool strong_password(const std::string& p) {
        if (p.size() < 8) return false;
        bool upp=false, low=false, dig=false, spec=false;
        for (char c : p) {
            if (std::isupper((unsigned char)c)) upp=true;
            else if (std::islower((unsigned char)c)) low=true;
            else if (std::isdigit((unsigned char)c)) dig=true;
            else spec=true;
        }
        return upp && low && dig && spec;
    }
