#include "Message.h"
#include "Encryptor.h"
#include <iostream>

Message::Message(const std::string& sender, const std::string& content)
    : sender(sender), content(content) {}

std::string Message::getSender() const {
    return sender;
}

std::string Message::getEncryptedText() const {
    return content;
}

std::string Message::decrypt(const std::string& key) const {
    return Encryptor::xorEncryptDecrypt(content, key);
}

std::ostream& operator<<(std::ostream& os, const Message& msg) {
    os << "[" << msg.getSender() << "]: " << msg.content;
    return os;
}