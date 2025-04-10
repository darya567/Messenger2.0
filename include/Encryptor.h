#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include <string>

class Encryptor {
public:
    static std::string xorEncryptDecrypt(const std::string& text, const std::string& key);
};

#endif