#pragma once
#include <string>
#include "Util.h"

using namespace std;

enum class Role { ADMIN, EMPLOYEE };

class Account {
private:
    string m_username;
    string m_password;

public:
    Account(const string& username, const string& password) {}
    virtual ~Account() {}

    string getUsername() const {
        return "";
    }

    string getPassword() const {
        return "";
    }

    bool matchesUsername(const string& name) const {
        return false;
    }

    bool checkPassword(const string& password) const {
        return false;
    }

    void setPassword(const string& newPassword) {}

    virtual string toLine() const = 0;

    virtual Role getRole() const = 0;
};
