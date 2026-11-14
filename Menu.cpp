#include "Menu.h"
#include "Console.h"

Menu::Menu(const string& title, const string& exitLabel)
    : m_title(title), m_exitLabel(exitLabel) {
}

void Menu::run() {
    while (true) {
        Console::clearScreen();
        Console::printTitle(m_title);

        vector<string> options = getOptions();
        options.push_back(m_exitLabel);

        int choice = Console::chooseOption(options);
        if (choice == static_cast<int>(options.size())) {
            return;
        }

        handleChoice(choice);
        Console::pause();
    }
}

void Menu::printProfile(const string& username, const UserProfile& profile) {
    Console::printLine("Username: " + username);
    for (int i = 0; i < UserProfile::FIELD_COUNT; i++) {
        ProfileField field = static_cast<ProfileField>(i);
        Console::printLine(UserProfile::labelOf(field) + ": " + profile.get(field));
    }
}
