#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <vector>

class Admin : public User {
public:
    Admin(const std::string& name, int id);

    std::string getRole() const override;

    
    void kickUser(const User& user, std::vector<User>& userList);
};

#endif