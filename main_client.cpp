#include "ClientApp.h"
#include <iostream>

int main() {
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    ClientApp client(name, "127.0.0.1", 12345); 
    client.run();

    return 0;
}