#include "EmployeeMenu.h"
#include "Console.h"

using namespace std;

EmployeeMenu::EmployeeMenu(HrSystem& system, const string& username)
    : Menu("MENU EMPLOYEE (" + username + ")", Menu::LOGOUT_LABEL),
      m_system(system), m_strUsername(username) {
}

bool EmployeeMenu::forcePasswordChange() {
    Console::printLine("Day la lan dang nhap dau tien, ban phai doi mat khau.", Console::COLOR_TITLE);

    string strNewPassword;
    while (!this->askNewPassword(strNewPassword)) {
        Console::printLine("");
    }

    const string strError = this->m_system.changePassword(this->m_strUsername, strNewPassword);
    if (strError != "") {
        Console::printError(strError);
        Console::pause();
        return false;
    }

    Console::printSuccess("Doi mat khau thanh cong");
    Console::pause();
    return true;
}

vector<string> EmployeeMenu::getOptions() const {
    return {
        "Xem thong tin tai khoan",
        "Doi password"
    };
}

void EmployeeMenu::handleChoice(const int choice) {
    switch (choice) {
        case EmployeeMenu::CHOICE_SHOW_INFO:
            this->showMyInfo();
            break;

        case EmployeeMenu::CHOICE_CHANGE_PASSWORD:
            this->changePassword();
            break;

        default:
            break;
    }
}

void EmployeeMenu::showMyInfo() {
    UserProfile profile;
    const string strError = this->m_system.findEmployee(this->m_strUsername, profile);
    if (strError != "") {
        Console::printError(strError);
        return;
    }
    Menu::printProfile(this->m_strUsername, profile);
}

void EmployeeMenu::changePassword() {
    const string strCurrentPassword = Console::readPassword("Mat khau hien tai: ");
    if (!this->m_system.verifyPassword(this->m_strUsername, strCurrentPassword)) {
        Console::printError("Mat khau hien tai khong dung");
        return;
    }

    string strNewPassword;
    if (!this->askNewPassword(strNewPassword)) {
        return;
    }

    const string strError = this->m_system.changePassword(this->m_strUsername, strNewPassword);
    if (strError != "") {
        Console::printError(strError);
        return;
    }
    Console::printSuccess("Doi mat khau thanh cong");
}

bool EmployeeMenu::askNewPassword(string& newPassword) {
    const string strFirst = Console::readPassword("Mat khau moi: ");
    const string strError = this->m_system.checkNewPassword(this->m_strUsername, strFirst);
    if (strError != "") {
        Console::printError(strError);
        return false;
    }

    const string strSecond = Console::readPassword("Nhap lai mat khau moi: ");
    if (strFirst != strSecond) {
        Console::printError("Hai lan nhap mat khau moi khong khop");
        return false;
    }

    newPassword = strFirst;
    return true;
}
