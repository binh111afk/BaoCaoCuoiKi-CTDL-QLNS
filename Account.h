#pragma once
#include <string>
#include "Util.h"

enum class Role { ADMIN, EMPLOYEE };

class Account {
private:
    std::string m_username;
    std::string m_password;

public:
    Account(const std::string& username, const std::string& password) {}
    virtual ~Account() {}

    std::string getUsername() const {
        return "";
    }

    std::string getPassword() const {
        return "";
    }

    bool matchesUsername(const std::string& name) const {
        return false;
    }

    bool checkPassword(const std::string& password) const {
        return false;
    }

    void setPassword(const std::string& newPassword) {}

    virtual std::string toLine() const = 0;

    virtual Role getRole() const = 0;
};
