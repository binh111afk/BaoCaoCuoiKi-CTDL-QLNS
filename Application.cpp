#include "Application.h"
#include "Console.h"
#include "AdminMenu.h"
#include "EmployeeMenu.h"

using namespace std;

int Application::run() {
    vector<string> messages;
    const bool bReady = this->m_system.initialize(messages);

    const int iColor = bReady ? Console::COLOR_TITLE : Console::COLOR_ERROR;
    for (size_t iIndex = 0; iIndex < messages.size(); iIndex++) {
        Console::printLine(messages[iIndex], iColor);
    }

    if (!bReady) {
        Console::printError("Khong chuan bi duoc du lieu, chuong trinh se thoat");
        Console::pause();
        return 1;
    }

    if (!messages.empty()) {
        Console::pause();
    }

    while (true) {
        string strAccountName;
        Role eRole = Role::EMPLOYEE;
        if (!this->login(strAccountName, eRole)) {
            Console::printLine("Tam biet!");
            return 0;
        }

        switch (eRole) {
            case Role::ADMIN: {
                AdminMenu adminMenu(this->m_system, strAccountName);
                adminMenu.run();
                break;
            }

            case Role::EMPLOYEE: {
                EmployeeMenu employeeMenu(this->m_system, strAccountName);
                if (!this->m_system.needsPasswordChange(strAccountName) || employeeMenu.forcePasswordChange()) {
                    employeeMenu.run();
                }
                break;
            }

            default:
                break;
        }
    }
}

bool Application::login(string& accountName, Role& role) {
    Console::clearScreen();
    Console::printTitle("DANG NHAP");
    Console::printLine("(De trong User de thoat)", Console::COLOR_LABEL);

    int iFails = 0;
    while (iFails < Application::MAX_FAILS) {
        const string strUsername = Console::readLine("User: ");
        if (strUsername == "") {
            return false;
        }

        const string strPassword = Console::readPassword("Pass: ");
        if (this->m_system.login(strUsername, strPassword, role, accountName)) {
            return true;
        }

        iFails++;
        if (iFails < Application::MAX_FAILS) {
            Console::printError("Sai tai khoan hoac mat khau. Con " + to_string(Application::MAX_FAILS - iFails) + " lan thu.");
        }
    }

    Console::printError("Sai " + to_string(Application::MAX_FAILS) + " lan, chuong trinh ket thuc.");
    Console::pause();
    return false;
}
