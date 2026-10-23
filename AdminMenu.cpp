#include "AdminMenu.h"
#include "Console.h"
#include "Validator.h"

AdminMenu::AdminMenu(HrSystem& system, const string& username) {}

vector<string> AdminMenu::getOptions() const {
    return vector<string>();
}

void AdminMenu::handleChoice(int choice) {}

void AdminMenu::addEmployee() {}

void AdminMenu::removeEmployee() {}

void AdminMenu::findEmployee() {}

void AdminMenu::updateEmployee() {}

void AdminMenu::showAllEmployees() {}
