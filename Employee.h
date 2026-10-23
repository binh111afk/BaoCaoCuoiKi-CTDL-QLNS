#pragma once
#include <string>
#include "Account.h"

class Employee : public Account {
private:
    bool m_needsPasswordChange;

public:
    Employee(const std::string& username = "", const std::string& password = "",
             bool needsPasswordChange = false) {}

    static std::string defaultPassword() {
        return "";
    }

    static Employee createNew(const std::string& username) {
        return Employee();
    }

    static bool fromLine(const std::string& line, Employee& out) {
        return false;
    }

    std::string toLine() const override {
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
