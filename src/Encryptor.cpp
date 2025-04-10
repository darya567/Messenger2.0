#include "Encryptor.h"

std::string Encryptor::xorEncryptDecrypt(const std::string& text, const std::string& key) {
    std::string output = text;
    for (size_t i = 0; i < text.size(); ++i) {
        output[i] = text[i] ^ key[i % key.size()];
    }
    return output;
}