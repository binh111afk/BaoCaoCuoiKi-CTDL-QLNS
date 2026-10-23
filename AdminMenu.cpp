#include "AdminMenu.h"
#include "Console.h"
#include "Validator.h"

AdminMenu::AdminMenu(HrSystem& system, const std::string& username) {}

std::vector<std::string> AdminMenu::getOptions() const {
    return std::vector<std::string>();
}

void AdminMenu::handleChoice(int choice) {}

void AdminMenu::addEmployee() {}

void AdminMenu::removeEmployee() {}

void AdminMenu::findEmployee() {}

void AdminMenu::updateEmployee() {}

void AdminMenu::showAllEmployees() {}
