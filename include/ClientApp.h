#ifndef CLIENT_APP_H
#define CLIENT_APP_H

#include <string>

class ClientApp {
private:
    int sock;
    std::string username;
    std::string encryptionKey = "mysecretkey";

public:
    ClientApp(const std::string& name, const std::string& host, int port);
    void run();

    ~ClientApp();
};

#endif