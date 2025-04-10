#include "ServerApp.h"
#include "Encryptor.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

ServerApp::ServerApp(int port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    FD_ZERO(&masterSet);
    FD_SET(serverSocket, &masterSet);
    maxFd = serverSocket;

    std::cout << "Server listening on port " << port << std::endl;
}

void ServerApp::run() {
    while (true) {
        fd_set readSet = masterSet;

        if (select(maxFd + 1, &readSet, nullptr, nullptr, nullptr) < 0) {
            perror("select error");
            exit(EXIT_FAILURE);
        }

        for (int fd = 0; fd <= maxFd; ++fd) {
            if (FD_ISSET(fd, &readSet)) {
                if (fd == serverSocket) {

                    int clientSocket = accept(serverSocket, nullptr, nullptr);
                    if (clientSocket < 0) {
                        perror("Accept failed");
                        continue;
                    }
                    FD_SET(clientSocket, &masterSet);
                    if (clientSocket > maxFd) maxFd = clientSocket;

                    clients[clientSocket] = "Client_" + std::to_string(clientSocket);
                    std::cout << "New client connected: " << clients[clientSocket] << std::endl;
                } else {
   
                    char buffer[BUFFER_SIZE] = {0};
                    int bytesRead = read(fd, buffer, BUFFER_SIZE);
                    if (bytesRead <= 0) {
                        std::cout << "Client disconnected: " << clients[fd] << std::endl;
                        close(fd);
                        FD_CLR(fd, &masterSet);
                        clients.erase(fd);
                    } else {
                        std::string encryptedMessage(buffer, bytesRead);
                        encryptedHistory.push_back(encryptedMessage);


                        for (auto& [clientFd, name] : clients) {
                            if (clientFd != fd) {
                                send(clientFd, encryptedMessage.c_str(), encryptedMessage.size(), 0);
                            }
                        }

                        std::cout << "Encrypted message received from " << clients[fd] << ": " << encryptedMessage << std::endl;
                    }
                }
            }
        }
    }
}

ServerApp::~ServerApp() {
    for (int fd = 0; fd <= maxFd; ++fd) {
        if (FD_ISSET(fd, &masterSet)) {
            close(fd);
        }
    }
}