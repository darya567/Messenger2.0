#include "ClientApp.h"
#include "Encryptor.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define BUFFER_SIZE 1024

ClientApp::ClientApp(const std::string& name, const std::string& host, int port)
    : username(name) {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &serverAddr.sin_addr);

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    send(sock, username.c_str(), username.size(), 0);

    std::cout << "Connected to server as " << username << std::endl;
    std::cout << "Type your message or /kick <username> (if you're admin)\n";

}

void ClientApp::run() {
    fd_set readfds;

    while (true) {
        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);
        FD_SET(STDIN_FILENO, &readfds);

        int maxfd = std::max(sock, STDIN_FILENO) + 1;
        int activity = select(maxfd, &readfds, nullptr, nullptr, nullptr);

        if (activity < 0) {
            perror("select error");
            break;
        }

        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            std::string input;
            std::getline(std::cin, input);
            if (input.empty()) continue;

            std::string encrypted = Encryptor::xorEncryptDecrypt(input, encryptionKey);
            send(sock, encrypted.c_str(), encrypted.size(), 0);
        }

        if (FD_ISSET(sock, &readfds)) {
            char buffer[BUFFER_SIZE] = {0};
            int bytesRead = recv(sock, buffer, BUFFER_SIZE, 0);
            if (bytesRead <= 0) {
                std::cout << "Server disconnected.\n";
                break;
            }

            std::string encrypted(buffer, bytesRead);
            std::string decrypted = Encryptor::xorEncryptDecrypt(encrypted, encryptionKey);
            std::cout << "[MESSAGE] " << decrypted << std::endl;
        }
    }
}

ClientApp::~ClientApp() {
    close(sock);

}



