#include "Application.h"
#include "Console.h"
#include "AdminMenu.h"
#include "EmployeeMenu.h"

int Application::run() {
    vector<string> messages;
    bool ready = m_system.initialize(messages);

    int color = Console::COLOR_TITLE;
    if (!ready) {
        color = Console::COLOR_ERROR;
    }
    for (size_t i = 0; i < messages.size(); i++) {
        Console::printLine(messages[i], color);
    }

    if (!ready) {
        Console::printError("Khong chuan bi duoc du lieu, chuong trinh se thoat");
        Console::pause();
        return 1;
    }

    if (!messages.empty()) {
        Console::pause();
    }

    while (true) {
        string accountName;
        Role role = Role::EMPLOYEE;
        if (!login(accountName, role)) {
            Console::printLine("Tam biet!");
            return 0;
        }

        if (role == Role::ADMIN) {
            AdminMenu menu(m_system, accountName);
            menu.run();
        } else {
            EmployeeMenu menu(m_system, accountName);
            bool canEnter = true;
            if (m_system.needsPasswordChange(accountName)) {
                canEnter = menu.forcePasswordChange();
                Console::pause();
            }
            if (canEnter) {
                menu.run();
            }
        }
    }
}

bool Application::login(string& accountName, Role& role) {
    Console::clearScreen();
    Console::printTitle("DANG NHAP");
    Console::printLine("(De trong User de thoat)", Console::COLOR_LABEL);

    int fails = 0;
    while (fails < MAX_FAILS) {
        string username = Console::readLine("User: ");
        if (username == "") {
            return false;
        }

        string password = Console::readPassword("Pass: ");
        if (m_system.login(username, password, role, accountName)) {
            return true;
        }

        fails++;
        if (fails < MAX_FAILS) {
            Console::printError("Sai tai khoan hoac mat khau. Con " + to_string(MAX_FAILS - fails) + " lan thu.");
        }
    }

    Console::printError("Sai " + to_string(MAX_FAILS) + " lan, chuong trinh ket thuc.");
    Console::pause();
    return false;
}
