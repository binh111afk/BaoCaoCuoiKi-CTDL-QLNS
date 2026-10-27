#include "HrSystem.h"
#include "Util.h"
#include "Validator.h"

HrSystem::HrSystem() : 
    m_admins ("data/Administrators.txt"),
    m_employees("data/Employees.txt") {}

bool HrSystem::initialize(vector<string>& messages) {
    return loadFiles(messages)
        && removeDuplicateEmployees(messages)
        && createDefaultAdmins(messages);
}

bool HrSystem::login(const string& username, const string& password,
                     Role& role, string& accountName) {
    return false;
}

bool HrSystem::needsPasswordChange(const string& username) {
    return false;
}

bool HrSystem::verifyPassword(const string& username, const string& password) {
    return false;
}

string HrSystem::checkNewUsername(const string& username) {
    return "";
}

string HrSystem::checkNewPassword(const string& username, const string& newPassword) {
    return "";
}

string HrSystem::addEmployee(const string& username, const UserProfile& profile) {
    return "";
}

string HrSystem::removeEmployee(const string& username) {
    return "";
}

string HrSystem::findEmployee(const string& username, UserProfile& profile) {
    return "";
}

string HrSystem::updateField(const string& username, ProfileField field,
                             const string& value) {
    return "";
}

void HrSystem::listEmployees(vector<string>& usernames) {}

string HrSystem::changePassword(const string& username, const string& newPassword) {
    return "";
}

bool HrSystem::isUsernameTaken(const string& username) const {
    return false;
}

string HrSystem::profilePath(const string& username) {
    return "";
}

bool HrSystem::loadFiles(vector<string>& messages) {
    if (!Util::ensureFolder("data/users")) {
        messages.push_back("Khong tao duoc thu muc data/users");
        return false;
    }

    if (!m_admins.load()) {
        if (!m_admins.save()) {
            messages.push_back("Khong tao duoc file data/Administrators.txt");
            return false;
        }
    }
    if (!m_employees.load()) {
        if (!m_employees.save()) {
            messages.push_back("Khong tao duoc file data/Employees.txt");
            return false;
        }
    }
    return true;
}

bool HrSystem::removeDuplicateEmployees(vector<string>& messages) {
    bool removed = false;
    for (int i = m_employees.size() - 1; i >= 0; i--) {
        if (m_admins.indexOf(m_employees.at(i).getUsername()) != -1) {
            m_employees.removeAt(i);
            removed = true;
        }
    }
    for (int i = m_employees.size() - 1; i >= 0; i--) {
        if (m_employees.indexOf(m_employees.at(i).getUsername()) != i) {
            m_employees.removeAt(i);
            removed = true;
        }
    }
    if (removed && !m_employees.save()) {
        messages.push_back("Khong ghi duoc file data/Employees.txt");
        return false;
    }
    return true;
}

bool HrSystem::createDefaultAdmins(vector<string>& messages) {
    bool created = false;
    int number = 1;
    while (m_admins.size() < 3) {
        string name = "admin" + to_string(number);
        number++;
        if (isUsernameTaken(name)) {
            continue;
        }
        m_admins.add(Admin(name, "123456"));
        messages.push_back("Da tao admin mac dinh: " + name + " / 123456");
        created = true;
    }

    if (created) {
        if (!m_admins.save()) {
            messages.push_back("Khong ghi duoc file data/Administrators.txt");
            return false;
        }
    }
    
    return true;
}
