#pragma once
#include <string>
#include <vector>
#include "Account.h"
#include "Admin.h"
#include "Employee.h"
#include "AccountList.h"
#include "UserProfile.h"

class HrSystem {
private:
    bool isUsernameTaken(const std::string& username) const;

    static std::string profilePath(const std::string& username);

    AccountList<Admin> m_admins;
    AccountList<Employee> m_employees;

public:
    HrSystem();

    bool initialize(std::vector<std::string>& messages);

    bool login(const std::string& username, const std::string& password,
               Role& role, std::string& accountName);

    bool needsPasswordChange(const std::string& username);

    bool verifyPassword(const std::string& username, const std::string& password);

    std::string checkNewUsername(const std::string& username);

    std::string checkNewPassword(const std::string& username, const std::string& newPassword);

    std::string addEmployee(const std::string& username, const UserProfile& profile);

    std::string removeEmployee(const std::string& username);

    std::string findEmployee(const std::string& username, UserProfile& profile);

    std::string updateField(const std::string& username, ProfileField field, const std::string& value);

    void listEmployees(std::vector<std::string>& usernames);

    std::string changePassword(const std::string& username, const std::string& newPassword);
};
