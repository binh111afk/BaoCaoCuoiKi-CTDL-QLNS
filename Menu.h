#pragma once
#include <string>
#include <vector>
#include "UserProfile.h"

class Menu {
private:
    virtual std::vector<std::string> getOptions() const = 0;

    virtual void handleChoice(int choice) = 0;

    std::string m_title;
    std::string m_exitLabel;

public:
    Menu(const std::string& title, const std::string& exitLabel);
    virtual ~Menu() {}

    void run();

    static void printProfile(const std::string& username, const UserProfile& profile);
};
