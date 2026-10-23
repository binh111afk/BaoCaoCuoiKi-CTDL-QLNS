#pragma once
#include <string>
#include <vector>
#include "Menu.h"
#include "HrSystem.h"

class AdminMenu : public Menu {
private:
    std::vector<std::string> getOptions() const override;

    void handleChoice(int choice) override;

    void addEmployee();

    void removeEmployee();

    void findEmployee();

    void updateEmployee();

    void showAllEmployees();

    HrSystem& m_system;

public:
    AdminMenu(HrSystem& system, const std::string& username);
};
