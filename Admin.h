#pragma once
#include <string>
#include "Account.h"

class Admin : public Account {
public:
    Admin(const std::string& username = "", const std::string& password = "") {}

    static bool fromLine(const std::string& line, Admin& out) {
        return false;
    }

    std::string toLine() const override {
        return "";
    }

    Role getRole() const override {
        return Role();
    }
};
