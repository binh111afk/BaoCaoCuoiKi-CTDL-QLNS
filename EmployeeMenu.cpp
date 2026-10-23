#include "EmployeeMenu.h"
#include "Console.h"

EmployeeMenu::EmployeeMenu(HrSystem& system, const string& username) {}

bool EmployeeMenu::forcePasswordChange() {
    return false;
}

vector<string> EmployeeMenu::getOptions() const {
    return vector<string>();
}

void EmployeeMenu::handleChoice(int choice) {}

void EmployeeMenu::showMyInfo() {}

void EmployeeMenu::changePassword() {}

bool EmployeeMenu::askNewPassword(string& newPassword) {
    return false;
}
