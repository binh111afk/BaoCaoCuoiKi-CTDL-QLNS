#pragma once
#include <string>
#include <vector>
#include "Menu.h"
#include "HrSystem.h"

class EmployeeMenu : public Menu {
private:
    std::vector<std::string> getOptions() const override;

    void handleChoice(int choice) override;

    void showMyInfo();

    void changePassword();

    bool askNewPassword(std::string& newPassword);

    HrSystem& m_system;
    std::string m_username;

public:
    EmployeeMenu(HrSystem& system, const std::string& username);

    bool forcePasswordChange();
};
