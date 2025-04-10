#include "User.h"

User::User(const std::string& name, int id) : username(name), userId(id) {}

std::string User::getName() const {
    return username;
}

int User::getId() const {
    return userId;
}

std::string User::getRole() const {
    return "User";
}

bool User::operator==(const User& other) const {
    return userId == other.userId;
}

int User::generateId() {
    static int currentId = 0;
    return ++currentId;
}