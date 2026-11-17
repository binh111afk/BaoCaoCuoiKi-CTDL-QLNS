#include <sstream>
#include "Employee.h"

using namespace std;

const string Employee::DEFAULT_PASSWORD = "111111";
const char* const Employee::FLAG_NEEDED = "1";
const char* const Employee::FLAG_NOT_NEEDED = "0";

Employee::Employee(const string& username, const string& password,
                   const bool needsPasswordChange)
    : Account(username, password), m_bNeedsPasswordChange(needsPasswordChange) {
}

string Employee::defaultPassword() {
    return Employee::DEFAULT_PASSWORD;
}

Employee Employee::createNew(const string& username) {
    return Employee(username, Employee::defaultPassword(), true);
}

bool Employee::fromLine(const string& line, Employee& out) {
    istringstream stream = istringstream(line);
    string strUsername;
    string strPassword;
    string strFlag;
    string strExtra;

    stream >> strUsername >> strPassword >> strFlag;
    if (!stream) {
        return false;
    }

    if (stream >> strExtra) {
        return false;
    }

    if (strFlag != Employee::FLAG_NOT_NEEDED && strFlag != Employee::FLAG_NEEDED) {
        return false;
    }

    out = Employee(strUsername, strPassword, strFlag == Employee::FLAG_NEEDED);
    return true;
}

string Employee::toLine() const {
    const string strFlag = this->m_bNeedsPasswordChange ? Employee::FLAG_NEEDED : Employee::FLAG_NOT_NEEDED;
    return this->getUsername() + " " + this->getPassword() + " " + strFlag;
}

Role Employee::getRole() const {
    return Role::EMPLOYEE;
}

bool Employee::needsPasswordChange() const {
    return this->m_bNeedsPasswordChange;
}

void Employee::setNeedsPasswordChange(const bool value) {
    this->m_bNeedsPasswordChange = value;
}
