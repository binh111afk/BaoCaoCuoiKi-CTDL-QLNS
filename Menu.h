#pragma once
#include <string>
#include <vector>
#include "UserProfile.h"

using namespace std;

class Menu {
private:
    virtual vector<string> getOptions() const = 0;

    virtual void handleChoice(int choice) = 0;

    string m_title;
    string m_exitLabel;

public:
    Menu(const string& title, const string& exitLabel);
    virtual ~Menu() {}

    void run();

    static void printProfile(const string& username, const UserProfile& profile);
};
