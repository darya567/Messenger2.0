#include "Admin.h"
#include <algorithm>
#include <iostream>

Admin::Admin(const std::string& name, int id) : User(name, id) {}

std::string Admin::getRole() const {
    return "Admin";
}

void Admin::kickUser(const User& user, std::vector<User>& userList) {
    auto it = std::remove_if(userList.begin(), userList.end(),
        [&user](const User& u) { return u == user; });

    if (it != userList.end()) {
        userList.erase(it, userList.end());
        std::cout << "User " << user.getName() << " has been kicked out.\n";
    } else {
        std::cout << "User not found.\n";
    }
}