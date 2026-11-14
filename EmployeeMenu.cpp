#include "EmployeeMenu.h"
#include "Console.h"

EmployeeMenu::EmployeeMenu(HrSystem& system, const string& username)
    : Menu("MENU EMPLOYEE (" + username + ")", "Thoat (dang xuat)"),
      m_system(system), m_username(username) {
}

bool EmployeeMenu::forcePasswordChange() {
    Console::printLine("Day la lan dang nhap dau tien, ban phai doi mat khau.", Console::COLOR_TITLE);

    string newPassword;
    while (!askNewPassword(newPassword)) {
        Console::printLine("");
    }

    string error = m_system.changePassword(m_username, newPassword);
    if (error != "") {
        Console::printError(error);
        return false;
    }
    Console::printSuccess("Doi mat khau thanh cong");
    return true;
}

vector<string> EmployeeMenu::getOptions() const {
    return {
        "Xem thong tin tai khoan",
        "Doi password"
    };
}

void EmployeeMenu::handleChoice(int choice) {
    if (choice == 1) {
        showMyInfo();
    } else if (choice == 2) {
        changePassword();
    }
}

void EmployeeMenu::showMyInfo() {
    UserProfile profile;
    string error = m_system.findEmployee(m_username, profile);
    if (error != "") {
        Console::printError(error);
        return;
    }
    printProfile(m_username, profile);
}

void EmployeeMenu::changePassword() {
    string currentPassword = Console::readPassword("Mat khau hien tai: ");
    if (!m_system.verifyPassword(m_username, currentPassword)) {
        Console::printError("Mat khau hien tai khong dung");
        return;
    }

    string newPassword;
    if (!askNewPassword(newPassword)) {
        return;
    }

    string error = m_system.changePassword(m_username, newPassword);
    if (error != "") {
        Console::printError(error);
        return;
    }
    Console::printSuccess("Doi mat khau thanh cong");
}

bool EmployeeMenu::askNewPassword(string& newPassword) {
    string first = Console::readPassword("Mat khau moi: ");
    string error = m_system.checkNewPassword(m_username, first);
    if (error != "") {
        Console::printError(error);
        return false;
    }

    string second = Console::readPassword("Nhap lai mat khau moi: ");
    if (first != second) {
        Console::printError("Hai lan nhap mat khau moi khong khop");
        return false;
    }

    newPassword = first;
    return true;
}
