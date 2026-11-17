#include "HrSystem.h"
#include "Util.h"
#include "Validator.h"

using namespace std;

const string HrSystem::DEFAULT_ADMIN_PREFIX = "admin";
const string HrSystem::DEFAULT_ADMIN_PASSWORD = "123456";
const string HrSystem::ADMIN_FILE_PATH = "data/Administrators.txt";
const string HrSystem::EMPLOYEE_FILE_PATH = "data/Employees.txt";
const string HrSystem::PROFILE_FOLDER = "data/users";
const string HrSystem::PROFILE_EXTENSION = ".txt";
const string HrSystem::FILE_ERROR = "Khong ghi duoc file du lieu";
const string HrSystem::EMPLOYEE_NOT_FOUND = "Nhan vien khong ton tai";

HrSystem::HrSystem() :
    m_admins(HrSystem::ADMIN_FILE_PATH),
    m_employees(HrSystem::EMPLOYEE_FILE_PATH) {
}

bool HrSystem::initialize(vector<string>& messages) {
    return this->loadFiles(messages)
        && this->removeDuplicateEmployees(messages)
        && this->createDefaultAdmins(messages);
}

bool HrSystem::login(const string& username, const string& password,
                     Role& role, string& accountName) {

    int iIndex = this->m_admins.indexOf(username);
    if (iIndex != AccountList<Admin>::NOT_FOUND && this->m_admins.at(iIndex).checkPassword(password)) {
        role = this->m_admins.at(iIndex).getRole();
        accountName = this->m_admins.at(iIndex).getUsername();
        return true;
    }

    iIndex = this->m_employees.indexOf(username);
    if (iIndex != AccountList<Employee>::NOT_FOUND && this->m_employees.at(iIndex).checkPassword(password)) {
        role = this->m_employees.at(iIndex).getRole();
        accountName = this->m_employees.at(iIndex).getUsername();
        return true;
    }

    return false;
}

bool HrSystem::needsPasswordChange(const string& username) {
    const int iIndex = this->m_employees.indexOf(username);
    if (iIndex == AccountList<Employee>::NOT_FOUND) {
        return false;
    }
    return this->m_employees.at(iIndex).needsPasswordChange();
}

bool HrSystem::verifyPassword(const string& username, const string& password) {
    const int iIndex = this->m_employees.indexOf(username);
    if (iIndex == AccountList<Employee>::NOT_FOUND) {
        return false;
    }
    return this->m_employees.at(iIndex).checkPassword(password);
}

string HrSystem::checkNewUsername(const string& username) {
    const string strError = Validator::checkUsername(username);
    if (strError != "") {
        return strError;
    }
    if (this->isUsernameTaken(username)) {
        return "Username da ton tai";
    }

    return "";
}

string HrSystem::checkNewPassword(const string& username, const string& newPassword) {
    const string strError = Validator::checkPassword(newPassword);
    if (!strError.empty()) {
        return strError;
    }
    if (newPassword == Employee::defaultPassword()) {
        return "Mat khau moi khong duoc trung voi mat khau mac dinh";
    }

    const int iIndex = this->m_employees.indexOf(username);
    if (iIndex != AccountList<Employee>::NOT_FOUND && this->m_employees.at(iIndex).checkPassword(newPassword)) {
        return "Mat khau moi khong duoc trung voi mat khau cu";
    }
    return "";
}

string HrSystem::addEmployee(const string& username, const UserProfile& profile) {
    const string strPath = HrSystem::profilePath(username);
    if (!Util::writeLines(strPath, profile.toLines())) {
        return HrSystem::FILE_ERROR;
    }

    this->m_employees.add(Employee::createNew(username));
    if (!this->m_employees.save()) {
        // Hoàn tác nếu không ghi được danh sách
        Util::deleteFile(strPath);
        return HrSystem::FILE_ERROR;
    }

    return "";
}

string HrSystem::removeEmployee(const string& username) {
    const int iIndex = this->m_employees.indexOf(username);
    if (iIndex == AccountList<Employee>::NOT_FOUND) {
        return HrSystem::EMPLOYEE_NOT_FOUND;
    }

    this->m_employees.removeAt(iIndex);
    if (!this->m_employees.save()) {
        return HrSystem::FILE_ERROR;
    }

    Util::deleteFile(HrSystem::profilePath(username));
    return "";
}

string HrSystem::findEmployee(const string& username, UserProfile& profile) {
    if (this->m_employees.indexOf(username) == AccountList<Employee>::NOT_FOUND) {
        return HrSystem::EMPLOYEE_NOT_FOUND;
    }

    vector<string> lines;
    if (!Util::readLines(HrSystem::profilePath(username), lines)) {
        return "Khong doc duoc file ho so";
    }

    if (!UserProfile::fromLines(lines, profile)) {
        return "File ho so khong du thong tin";
    }

    return "";
}

string HrSystem::updateField(const string& username, const ProfileField field,
                             const string& value) {
    const string strError = Validator::checkField(field, value);
    if (!strError.empty()) {
        return strError;
    }

    UserProfile profile;
    const string strFindError = this->findEmployee(username, profile);
    if (!strFindError.empty()) {
        return strFindError;
    }

    profile.set(field, value);

    if (!Util::writeLines(HrSystem::profilePath(username), profile.toLines())) {
        return HrSystem::FILE_ERROR;
    }

    return "";
}

void HrSystem::listEmployees(vector<string>& usernames) {
    this->m_employees.sortByUsername();
    usernames.clear();
    for (int iIndex = 0; iIndex < this->m_employees.size(); iIndex++) {
        usernames.push_back(this->m_employees.at(iIndex).getUsername());
    }
}

string HrSystem::changePassword(const string& username, const string& newPassword) {
    const int iIndex = this->m_employees.indexOf(username);
    if (iIndex == AccountList<Employee>::NOT_FOUND) {
        return HrSystem::EMPLOYEE_NOT_FOUND;
    }

    this->m_employees.at(iIndex).setPassword(newPassword);
    this->m_employees.at(iIndex).setNeedsPasswordChange(false);

    if (!this->m_employees.save()) {
        return HrSystem::FILE_ERROR;
    }

    return "";
}

bool HrSystem::isUsernameTaken(const string& username) const {
    return this->m_admins.indexOf(username) != AccountList<Admin>::NOT_FOUND
        || this->m_employees.indexOf(username) != AccountList<Employee>::NOT_FOUND;
}

string HrSystem::profilePath(const string& username) {
    return HrSystem::PROFILE_FOLDER + "/" + Util::toLower(username) + HrSystem::PROFILE_EXTENSION;
}

bool HrSystem::loadFiles(vector<string>& messages) {
    if (!Util::ensureFolder(HrSystem::PROFILE_FOLDER)) {
        messages.push_back("Khong tao duoc thu muc " + HrSystem::PROFILE_FOLDER);
        return false;
    }

    if (!this->m_admins.load() && !this->m_admins.save()) {
        messages.push_back("Khong tao duoc file " + HrSystem::ADMIN_FILE_PATH);
        return false;
    }

    if (!this->m_employees.load() && !this->m_employees.save()) {
        messages.push_back("Khong tao duoc file " + HrSystem::EMPLOYEE_FILE_PATH);
        return false;
    }
    return true;
}

bool HrSystem::removeDuplicateEmployees(vector<string>& messages) {
    bool bRemoved = false;
    for (int iIndex = this->m_employees.size() - 1; iIndex >= 0; iIndex--) {
        if (this->m_admins.indexOf(this->m_employees.at(iIndex).getUsername()) != AccountList<Admin>::NOT_FOUND) {
            this->m_employees.removeAt(iIndex);
            bRemoved = true;
        }
    }
    for (int iIndex = this->m_employees.size() - 1; iIndex >= 0; iIndex--) {
        if (this->m_employees.indexOf(this->m_employees.at(iIndex).getUsername()) != iIndex) {
            this->m_employees.removeAt(iIndex);
            bRemoved = true;
        }
    }
    if (bRemoved && !this->m_employees.save()) {
        messages.push_back("Khong ghi duoc file " + HrSystem::EMPLOYEE_FILE_PATH);
        return false;
    }
    return true;
}

bool HrSystem::createDefaultAdmins(vector<string>& messages) {
    bool bCreated = false;
    int iNumber = 1;
    while (this->m_admins.size() < HrSystem::DEFAULT_ADMIN_COUNT) {
        const string strName = HrSystem::DEFAULT_ADMIN_PREFIX + to_string(iNumber);
        iNumber++;
        if (this->isUsernameTaken(strName)) {
            continue;
        }
        this->m_admins.add(Admin(strName, HrSystem::DEFAULT_ADMIN_PASSWORD));
        messages.push_back("Da tao admin mac dinh: " + strName + " / " + HrSystem::DEFAULT_ADMIN_PASSWORD);
        bCreated = true;
    }

    if (bCreated) {
        if (!this->m_admins.save()) {
            messages.push_back("Khong ghi duoc file " + HrSystem::ADMIN_FILE_PATH);
            return false;
        }
    }

    return true;
}
