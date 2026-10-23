#pragma once
#include <string>
#include "Account.h"

using namespace std;

class Employee : public Account {
private:
    bool m_needsPasswordChange;

public:
    Employee(const string& username = "", const string& password = "",
             bool needsPasswordChange = false) {}

    static string defaultPassword() {
        return "";
    }

    static Employee createNew(const string& username) {
        return Employee();
    }

    static bool fromLine(const string& line, Employee& out) {
        return false;
    }

    string toLine() const override {
        return "";
    }

    Role getRole() const override {
        return Role();
    }

    bool needsPasswordChange() const {
        return false;
    }

    void setNeedsPasswordChange(bool value) {}
};
