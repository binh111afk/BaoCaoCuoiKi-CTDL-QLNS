#include "HrSystem.h"
#include "Util.h"
#include "Validator.h"

const std::string FILE_ERROR = "Khong ghi duoc file du lieu";

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

    int index = m_admins.indexOf(username);
    if (index != -1 && m_admins.at(index).checkPassword(password)) {
        role = m_admins.at(index).getRole();
        accountName = m_admins.at(index).getUsername();
        return true;
    }

    index = m_employees.indexOf(username);
    if (index != -1 && m_employees.at(index).checkPassword(password)) {
        role = m_employees.at(index).getRole();
        accountName = m_employees.at(index).getUsername();
        return true;
    }

    return false;
}

bool HrSystem::needsPasswordChange(const string& username) {
    int index = m_employees.indexOf(username);
    if (index == -1) {
        return false;
    }
    return m_employees.at(index).needsPasswordChange();
}

bool HrSystem::verifyPassword(const string& username, const string& password) {
    int index = m_employees.indexOf(username);
    if (index == -1) {
        return false;
    }
    return m_employees.at(index).checkPassword(password);
}

string HrSystem::checkNewUsername(const string& username) {
    string error = Validator::checkUsername(username);
    if (error != "") {
        return error;
    }
    if (isUsernameTaken(username)) {
        return "Username da ton tai";
    }
    
    return "";
}

string HrSystem::checkNewPassword(const string& username, const string& newPassword) {
    string err = Validator::checkPassword(newPassword);
    if (!err.empty()) {
        return err;
    }
    if (newPassword == Employee::defaultPassword()) {
        return "Mat khau moi khong duoc trung voi mat khau mac dinh";
    }
    
    int empIdx = m_employees.indexOf(username);
    if (empIdx != -1) {
        if (m_employees.at(empIdx).checkPassword(newPassword)) {
            return "Mat khau moi khong duoc trung voi mat khau cu";
        }
    }
    return "";
}

string HrSystem::addEmployee(const string& username, const UserProfile& profile) {
    string path = profilePath(username);
    if (!Util::writeLines(path, profile.toLines())) {
        return FILE_ERROR;
    }
    
    Employee newEmp = Employee::createNew(username);
    m_employees.add(newEmp);
    
    if (!m_employees.save()) {
        Util::deleteFile(path); // Hoàn tác nếu không ghi được danh sách
        return FILE_ERROR;
    }
    
    return "";
}

string HrSystem::removeEmployee(const string& username) {
    int empIdx = m_employees.indexOf(username);
    if (empIdx == -1) {
        return "Nhan vien khong ton tai";
    }
    
    m_employees.removeAt(empIdx);
    if (!m_employees.save()) {
        return FILE_ERROR;
    }
    
    Util::deleteFile(profilePath(username));
    return "";
}

string HrSystem::findEmployee(const string& username, UserProfile& profile) {
    int empIdx = m_employees.indexOf(username);
    if (empIdx == -1) {
        return "Nhan vien khong ton tai";
    }
    
    vector<string> lines;
    if (!Util::readLines(profilePath(username), lines)) {
        return "Khong doc duoc file ho so";
    }
    
    if (!UserProfile::fromLines(lines, profile)) {
        return "File ho so khong du thong tin";
    }
    
    return "";
}

string HrSystem::updateField(const string& username, ProfileField field,
                             const string& value) {
    string err = Validator::checkField(field, value);
    if (!err.empty()) {
        return err;
    }
    
    UserProfile profile;
    string findErr = findEmployee(username, profile);
    if (!findErr.empty()) {
        return findErr;
    }
    
    profile.set(field, value);
    
    if (!Util::writeLines(profilePath(username), profile.toLines())) {
        return FILE_ERROR;
    }
    
    return "";
}

void HrSystem::listEmployees(vector<string>& usernames) {
    m_employees.sortByUsername();
    usernames.clear();
    for (int i = 0; i < m_employees.size(); ++i) {
        usernames.push_back(m_employees.at(i).getUsername());
    }
}

string HrSystem::changePassword(const string& username, const string& newPassword) {
    int empIdx = m_employees.indexOf(username);
    if (empIdx == -1) {
        return "Nhan vien khong ton tai";
    }
    
    m_employees.at(empIdx).setPassword(newPassword);
    m_employees.at(empIdx).setNeedsPasswordChange(false);
    
    if (!m_employees.save()) {
        return FILE_ERROR;
    }
    
    return "";
}

bool HrSystem::isUsernameTaken(const string& username) const {
    return m_admins.indexOf(username) != -1 || m_employees.indexOf(username) != -1;
}

string HrSystem::profilePath(const string& username) {
    return "data/users/" + Util::toLower(username) + ".txt";
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