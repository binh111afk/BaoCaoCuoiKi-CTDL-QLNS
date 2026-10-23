#include "EmployeeMenu.h"
#include "Console.h"

EmployeeMenu::EmployeeMenu(HrSystem& system, const std::string& username) {}

bool EmployeeMenu::forcePasswordChange() {
    return false;
}

std::vector<std::string> EmployeeMenu::getOptions() const {
    return std::vector<std::string>();
}

void EmployeeMenu::handleChoice(int choice) {}

void EmployeeMenu::showMyInfo() {}

void EmployeeMenu::changePassword() {}

bool EmployeeMenu::askNewPassword(std::string& newPassword) {
    return false;
}
