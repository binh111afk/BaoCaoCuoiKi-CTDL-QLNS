#pragma once
#include <string>
#include <vector>
#include "Menu.h"
#include "HrSystem.h"

using namespace std;

class AdminMenu : public Menu {
private:
    vector<string> getOptions() const override;

    void handleChoice(int choice) override;

    void addEmployee();

    void removeEmployee();

    void findEmployee();

    void updateEmployee();

    void showAllEmployees();

    HrSystem& m_system;

public:
    AdminMenu(HrSystem& system, const string& username);
};
