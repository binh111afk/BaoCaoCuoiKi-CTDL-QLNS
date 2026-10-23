#pragma once
#include <string>
#include "Account.h"

using namespace std;

class Admin : public Account {
public:
    Admin(const string& username = "", const string& password = "") {}

    static bool fromLine(const string& line, Admin& out) {
        return false;
    }

    string toLine() const override {
        return "";
    }

    Role getRole() const override {
        return Role();
    }
};
