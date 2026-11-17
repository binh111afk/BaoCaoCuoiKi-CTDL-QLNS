#include "AdminMenu.h"
#include "Console.h"
#include "Validator.h"

using namespace std;

AdminMenu::AdminMenu(HrSystem& system, const string& username)
    : Menu("MENU ADMIN (" + username + ")", Menu::LOGOUT_LABEL), m_system(system) {
}

vector<string> AdminMenu::getOptions() const {
    return {
        "Them Employee",
        "Xoa Employee",
        "Tim Employee",
        "Cap nhat Employee",
        "Hien thi thong tin Employee"
    };
}

void AdminMenu::handleChoice(const int choice) {
    switch (choice) {
        case AdminMenu::CHOICE_ADD:
            this->addEmployee();
            break;

        case AdminMenu::CHOICE_REMOVE:
            this->removeEmployee();
            break;

        case AdminMenu::CHOICE_FIND:
            this->findEmployee();
            break;

        case AdminMenu::CHOICE_UPDATE:
            this->updateEmployee();
            break;

        case AdminMenu::CHOICE_SHOW_ALL:
            this->showAllEmployees();
            break;

        default:
            break;
    }
}

void AdminMenu::addEmployee() {
    const string strUsername = Console::readLine("Username: ");
    string strError = this->m_system.checkNewUsername(strUsername);
    if (strError != "") {
        Console::printError(strError);
        return;
    }

    UserProfile profile;
    for (int iField = 0; iField < UserProfile::FIELD_COUNT; iField++) {
        const ProfileField eField = static_cast<ProfileField>(iField);
        const string strValue = Console::readLine(UserProfile::labelOf(eField) + ": ");
        strError = Validator::checkField(eField, strValue);
        if (strError != "") {
            Console::printError(strError);
            return;
        }
        profile.set(eField, strValue);
    }

    strError = this->m_system.addEmployee(strUsername, profile);
    if (strError != "") {
        Console::printError(strError);
        return;
    }
    Console::printSuccess("Da them nhan vien " + strUsername + ". Mat khau mac dinh: " + Employee::defaultPassword());
}

void AdminMenu::removeEmployee() {
    const string strUsername = Console::readLine("Username can xoa: ");
    if (!Console::confirm("Xoa nhan vien " + strUsername + "?")) {
        Console::printLine("Da huy, khong xoa gi ca");
        return;
    }

    const string strError = this->m_system.removeEmployee(strUsername);
    if (strError != "") {
        Console::printError(strError);
        return;
    }
    Console::printSuccess("Da xoa nhan vien " + strUsername);
}

void AdminMenu::findEmployee() {
    const string strUsername = Console::readLine("Username can tim: ");

    UserProfile profile;
    const string strError = this->m_system.findEmployee(strUsername, profile);
    if (strError != "") {
        Console::printError(strError);
        return;
    }
    Menu::printProfile(strUsername, profile);
}

void AdminMenu::updateEmployee() {
    const string strUsername = Console::readLine("Username can cap nhat: ");
    const int iDoneChoice = UserProfile::FIELD_COUNT + 1;

    while (true) {
        UserProfile profile;
        string strError = this->m_system.findEmployee(strUsername, profile);
        if (strError != "") {
            Console::printError(strError);
            return;
        }

        vector<string> items;
        for (int iField = 0; iField < UserProfile::FIELD_COUNT; iField++) {
            const ProfileField eField = static_cast<ProfileField>(iField);
            items.push_back(UserProfile::labelOf(eField) + ": " + profile.get(eField));
        }
        items.push_back("Xong");

        Console::clearScreen();
        Console::printTitle("CAP NHAT: " + strUsername);
        const int iChoice = Console::chooseOption(items);
        if (iChoice == iDoneChoice) {
            return;
        }

        const int iFieldIndex = iChoice - 1;
        const ProfileField eChosenField = static_cast<ProfileField>(iFieldIndex);
        const string strValue = Console::readLine("Gia tri moi: ");
        strError = this->m_system.updateField(strUsername, eChosenField, strValue);
        if (strError != "") {
            Console::printError(strError);
        } else {
            Console::printSuccess("Da cap nhat");
        }
        Console::pause();
    }
}

void AdminMenu::showAllEmployees() {
    vector<string> usernames;
    this->m_system.listEmployees(usernames);
    if (usernames.empty()) {
        Console::printLine("Chua co nhan vien nao");
        return;
    }

    Console::printLine("STT | Username | Ho ten | So dien thoai | Email | Dia chi", Console::COLOR_TITLE);
    for (size_t iIndex = 0; iIndex < usernames.size(); iIndex++) {
        UserProfile profile;
        const string strError = this->m_system.findEmployee(usernames[iIndex], profile);
        if (strError != "") {
            Console::printError(to_string(iIndex + 1) + " | " + usernames[iIndex] + " | " + strError);
            continue;
        }

        Console::printLine(to_string(iIndex + 1) + " | " + usernames[iIndex]
            + " | " + profile.get(ProfileField::FULL_NAME)
            + " | " + profile.get(ProfileField::PHONE)
            + " | " + profile.get(ProfileField::EMAIL)
            + " | " + profile.get(ProfileField::ADDRESS));
    }
}
