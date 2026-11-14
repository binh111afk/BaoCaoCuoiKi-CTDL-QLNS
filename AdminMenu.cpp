#include "AdminMenu.h"
#include "Console.h"
#include "Validator.h"

AdminMenu::AdminMenu(HrSystem& system, const string& username)
    : Menu("MENU ADMIN (" + username + ")", "Thoat (dang xuat)"), m_system(system) {
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

void AdminMenu::handleChoice(int choice) {
    switch (choice) {
        case 1: addEmployee(); break;
        case 2: removeEmployee(); break;
        case 3: findEmployee(); break;
        case 4: updateEmployee(); break;
        case 5: showAllEmployees(); break;
    }
}

void AdminMenu::addEmployee() {
    string username = Console::readLine("Username: ");
    string error = m_system.checkNewUsername(username);
    if (error != "") {
        Console::printError(error);
        return;
    }

    UserProfile profile;
    for (int i = 0; i < UserProfile::FIELD_COUNT; i++) {
        ProfileField field = static_cast<ProfileField>(i);
        string value = Console::readLine(UserProfile::labelOf(field) + ": ");
        error = Validator::checkField(field, value);
        if (error != "") {
            Console::printError(error);
            return;
        }
        profile.set(field, value);
    }

    error = m_system.addEmployee(username, profile);
    if (error != "") {
        Console::printError(error);
        return;
    }
    Console::printSuccess("Da them nhan vien " + username + ". Mat khau mac dinh: " + Employee::defaultPassword());
}

void AdminMenu::removeEmployee() {
    string username = Console::readLine("Username can xoa: ");
    if (!Console::confirm("Xoa nhan vien " + username + "?")) {
        Console::printLine("Da huy, khong xoa gi ca");
        return;
    }

    string error = m_system.removeEmployee(username);
    if (error != "") {
        Console::printError(error);
        return;
    }
    Console::printSuccess("Da xoa nhan vien " + username);
}

void AdminMenu::findEmployee() {
    string username = Console::readLine("Username can tim: ");

    UserProfile profile;
    string error = m_system.findEmployee(username, profile);
    if (error != "") {
        Console::printError(error);
        return;
    }
    printProfile(username, profile);
}

void AdminMenu::updateEmployee() {
    string username = Console::readLine("Username can cap nhat: ");

    while (true) {
        UserProfile profile;
        string error = m_system.findEmployee(username, profile);
        if (error != "") {
            Console::printError(error);
            return;
        }

        vector<string> items;
        for (int i = 0; i < UserProfile::FIELD_COUNT; i++) {
            ProfileField field = static_cast<ProfileField>(i);
            items.push_back(UserProfile::labelOf(field) + ": " + profile.get(field));
        }
        items.push_back("Xong");

        Console::clearScreen();
        Console::printTitle("CAP NHAT: " + username);
        int choice = Console::chooseOption(items);
        if (choice == UserProfile::FIELD_COUNT + 1) {
            return;
        }

        ProfileField field = static_cast<ProfileField>(choice - 1);
        string value = Console::readLine("Gia tri moi: ");
        error = m_system.updateField(username, field, value);
        if (error != "") {
            Console::printError(error);
        } else {
            Console::printSuccess("Da cap nhat");
        }
        Console::pause();
    }
}

void AdminMenu::showAllEmployees() {
    vector<string> usernames;
    m_system.listEmployees(usernames);
    if (usernames.empty()) {
        Console::printLine("Chua co nhan vien nao");
        return;
    }

    Console::printLine("STT | Username | Ho ten | So dien thoai | Email | Dia chi", Console::COLOR_TITLE);
    for (size_t i = 0; i < usernames.size(); i++) {
        UserProfile profile;
        string error = m_system.findEmployee(usernames[i], profile);
        if (error != "") {
            Console::printError(to_string(i + 1) + " | " + usernames[i] + " | " + error);
            continue;
        }

        Console::printLine(to_string(i + 1) + " | " + usernames[i]
            + " | " + profile.get(ProfileField::FULL_NAME)
            + " | " + profile.get(ProfileField::PHONE)
            + " | " + profile.get(ProfileField::EMAIL)
            + " | " + profile.get(ProfileField::ADDRESS));
    }
}
