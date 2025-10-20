
    #include <openssl/evp.h>
    #include <openssl/rand.h>
    #include <sstream>
    #include <iomanip>
    #include "utils/crypto_utils.hpp"

    std::string hex_encode(const std::vector<unsigned char>& data) {
        std::ostringstream oss;
        oss << std::hex << std::setfill('0');
        for (auto c : data) oss << std::setw(2) << static_cast<int>(c);
        return oss.str();
    }

    std::vector<unsigned char> hex_decode(const std::string& hex) {
        std::vector<unsigned char> out;
        out.reserve(hex.size()/2);
        for (size_t i=0;i<hex.size();i+=2){
            unsigned int byte;
            std::stringstream ss;
            ss << std::hex << hex.substr(i,2);
            ss >> byte;
            out.push_back(static_cast<unsigned char>(byte));
        }
        return out;
    }

    bool pbkdf2_hash(const std::string& password, std::vector<unsigned char>& salt_out, std::vector<unsigned char>& hash_out,
                     int iterations, int salt_len, int dk_len) {
        salt_out.assign(salt_len, 0);
        if (RAND_bytes(salt_out.data(), salt_len) != 1) return false;
        hash_out.assign(dk_len, 0);
        if (PKCS5_PBKDF2_HMAC(password.c_str(), (int)password.size(),
                              salt_out.data(), salt_len,
                              iterations, EVP_sha256(), dk_len, hash_out.data()) != 1) {
            return false;
        }
        return true;
    }

    bool pbkdf2_verify(const std::string& password, const std::vector<unsigned char>& salt,
                       const std::vector<unsigned char>& expected_hash,
                       int iterations, int dk_len) {
        std::vector<unsigned char> hash(dk_len);
        if (PKCS5_PBKDF2_HMAC(password.c_str(), (int)password.size(),
                              salt.data(), (int)salt.size(),
                              iterations, EVP_sha256(), dk_len, hash.data()) != 1) {
            return false;
        }
        return CRYPTO_memcmp(hash.data(), expected_hash.data(), dk_len) == 0;
    }
