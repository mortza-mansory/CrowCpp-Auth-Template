#pragma once
#include <string>
#include <vector>

std::string hex_encode(const std::vector<unsigned char>& data);
std::vector<unsigned char> hex_decode(const std::string& hex);
bool pbkdf2_hash(const std::string& password, std::vector<unsigned char>& salt_out, std::vector<unsigned char>& hash_out,
                 int iterations = 100000, int salt_len = 16, int dk_len = 32);
bool pbkdf2_verify(const std::string& password, const std::vector<unsigned char>& salt,
                   const std::vector<unsigned char>& expected_hash,
                   int iterations = 100000, int dk_len = 32);
