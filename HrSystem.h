#pragma once
#include <string>
#include <vector>
#include "Account.h"
#include "Admin.h"
#include "Employee.h"
#include "AccountList.h"
#include "UserProfile.h"

using namespace std;

class HrSystem {
private:
    bool isUsernameTaken(const string& username) const;

    static string profilePath(const string& username);

    AccountList<Admin> m_admins;
    AccountList<Employee> m_employees;

public:
    HrSystem();

    bool initialize(vector<string>& messages);

    bool login(const string& username, const string& password,
               Role& role, string& accountName);

    bool needsPasswordChange(const string& username);

    bool verifyPassword(const string& username, const string& password);

    string checkNewUsername(const string& username);

    string checkNewPassword(const string& username, const string& newPassword);

    string addEmployee(const string& username, const UserProfile& profile);

    string removeEmployee(const string& username);

    string findEmployee(const string& username, UserProfile& profile);

    string updateField(const string& username, ProfileField field, const string& value);

    void listEmployees(vector<string>& usernames);

    string changePassword(const string& username, const string& newPassword);
};
