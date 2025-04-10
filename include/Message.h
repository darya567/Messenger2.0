#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message {
private:
    std::string sender;
    std::string content; 

public:
    Message(const std::string& sender, const std::string& content);

    std::string getSender() const;
    std::string getEncryptedText() const;

    std::string decrypt(const std::string& key) const;

    
    friend std::ostream& operator<<(std::ostream& os, const Message& msg);
};

#endif