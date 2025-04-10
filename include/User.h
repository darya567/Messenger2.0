#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string username;
    int userId;

public:
    User(const std::string& name, int id);

    virtual ~User() = default;

    std::string getName() const;
    int getId() const;

    virtual std::string getRole() const;

    bool operator==(const User& other) const;

    static int generateId();
};

#endif