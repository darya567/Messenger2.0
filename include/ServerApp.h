#ifndef SERVER_APP_H
#define SERVER_APP_H

#include <string>
#include <vector>
#include <map>

class ServerApp {
private:
    int serverSocket;
    fd_set masterSet;
    int maxFd;
    std::map<int, std::string> clients; 
    std::vector<std::string> encryptedHistory;
    const std::string encryptionKey = "mysecretkey";

public:
    ServerApp(int port);
    void run();

    ~ServerApp();
};

#endif