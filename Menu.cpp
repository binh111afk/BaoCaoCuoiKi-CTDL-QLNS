#include "Menu.h"
#include "Console.h"

using namespace std;

const string Menu::LOGOUT_LABEL = "Thoat (dang xuat)";

Menu::Menu(const string& title, const string& exitLabel)
    : m_strTitle(title), m_strExitLabel(exitLabel) {
}

void Menu::run() {
    while (true) {
        Console::clearScreen();
        Console::printTitle(this->m_strTitle);

        LinkedList<string> options = this->getOptions();
        options.addTail(this->m_strExitLabel);

        const int iChoice = Console::chooseOption(options);
        if (iChoice == options.getSize()) {
            return;
        }

        this->handleChoice(iChoice);
        Console::pause();
    }
}

void Menu::printProfile(const string& username, const UserProfile& profile) {
    Console::printLine("Username: " + username);
    for (int iField = 0; iField < UserProfile::FIELD_COUNT; iField++) {
        const ProfileField eField = static_cast<ProfileField>(iField);
        Console::printLine(UserProfile::labelOf(eField) + ": " + profile.get(eField));
    }
}
