#pragma once
#include <string>
#include <vector>
#include "Menu.h"
#include "HrSystem.h"

using namespace std;

class EmployeeMenu : public Menu {
private:
    vector<string> getOptions() const override;

    void handleChoice(int choice) override;

    void showMyInfo();

    void changePassword();

    bool askNewPassword(string& newPassword);

    HrSystem& m_system;
    string m_username;

public:
    EmployeeMenu(HrSystem& system, const string& username);

    bool forcePasswordChange();
};
