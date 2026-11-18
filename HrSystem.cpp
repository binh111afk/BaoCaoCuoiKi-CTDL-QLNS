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

bool HrSystem::initialize(LinkedList<string>& messages) {
    return this->loadFiles(messages)
        && this->removeDuplicateEmployees(messages)
        && this->createDefaultAdmins(messages);
}

bool HrSystem::login(const string& username, const string& password,
                     Role& role, string& accountName) {

    const Node<Admin>* const pAdmin = this->m_admins.search(username);
    if (pAdmin != nullptr && pAdmin->getData().checkPassword(password)) {
        role = pAdmin->getData().getRole();
        accountName = pAdmin->getData().getUsername();
        return true;
    }

    const Node<Employee>* const pEmployee = this->m_employees.search(username);
    if (pEmployee != nullptr && pEmployee->getData().checkPassword(password)) {
        role = pEmployee->getData().getRole();
        accountName = pEmployee->getData().getUsername();
        return true;
    }

    return false;
}

bool HrSystem::needsPasswordChange(const string& username) {
    const Node<Employee>* const pEmployee = this->m_employees.search(username);
    if (pEmployee == nullptr) {
        return false;
    }
    return pEmployee->getData().needsPasswordChange();
}

bool HrSystem::verifyPassword(const string& username, const string& password) {
    const Node<Employee>* const pEmployee = this->m_employees.search(username);
    if (pEmployee == nullptr) {
        return false;
    }
    return pEmployee->getData().checkPassword(password);
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

    const Node<Employee>* const pEmployee = this->m_employees.search(username);
    if (pEmployee != nullptr && pEmployee->getData().checkPassword(newPassword)) {
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
    Node<Employee>* const pEmployee = this->m_employees.search(username);
    if (pEmployee == nullptr) {
        return HrSystem::EMPLOYEE_NOT_FOUND;
    }

    this->m_employees.remove(pEmployee);
    if (!this->m_employees.save()) {
        return HrSystem::FILE_ERROR;
    }

    Util::deleteFile(HrSystem::profilePath(username));
    return "";
}

string HrSystem::findEmployee(const string& username, UserProfile& profile) {
    if (this->m_employees.search(username) == nullptr) {
        return HrSystem::EMPLOYEE_NOT_FOUND;
    }

    LinkedList<string> lines;
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

void HrSystem::listEmployees(LinkedList<string>& usernames) {
    this->m_employees.sortByUsername();
    usernames.clear();
    for (Node<Employee>* pEmployee = this->m_employees.getHead(); pEmployee != nullptr; pEmployee = pEmployee->getNext()) {
        usernames.addTail(pEmployee->getData().getUsername());
    }
}

string HrSystem::changePassword(const string& username, const string& newPassword) {
    Node<Employee>* const pEmployee = this->m_employees.search(username);
    if (pEmployee == nullptr) {
        return HrSystem::EMPLOYEE_NOT_FOUND;
    }

    pEmployee->getData().setPassword(newPassword);
    pEmployee->getData().setNeedsPasswordChange(false);

    if (!this->m_employees.save()) {
        return HrSystem::FILE_ERROR;
    }

    return "";
}

bool HrSystem::isUsernameTaken(const string& username) const {
    return this->m_admins.search(username) != nullptr
        || this->m_employees.search(username) != nullptr;
}

string HrSystem::profilePath(const string& username) {
    return HrSystem::PROFILE_FOLDER + "/" + Util::toLower(username) + HrSystem::PROFILE_EXTENSION;
}

bool HrSystem::loadFiles(LinkedList<string>& messages) {
    if (!Util::ensureFolder(HrSystem::PROFILE_FOLDER)) {
        messages.addTail("Khong tao duoc thu muc " + HrSystem::PROFILE_FOLDER);
        return false;
    }

    if (!this->m_admins.load() && !this->m_admins.save()) {
        messages.addTail("Khong tao duoc file " + HrSystem::ADMIN_FILE_PATH);
        return false;
    }

    if (!this->m_employees.load() && !this->m_employees.save()) {
        messages.addTail("Khong tao duoc file " + HrSystem::EMPLOYEE_FILE_PATH);
        return false;
    }
    return true;
}

bool HrSystem::removeDuplicateEmployees(LinkedList<string>& messages) {
    bool bRemoved = false;
    Node<Employee>* pEmployee = this->m_employees.getHead();
    while (pEmployee != nullptr) {
        Node<Employee>* const pNext = pEmployee->getNext();
        const string strName = pEmployee->getData().getUsername();
        const bool bDuplicate = this->m_admins.search(strName) != nullptr
            || this->m_employees.search(strName) != pEmployee;
        if (bDuplicate) {
            this->m_employees.remove(pEmployee);
            bRemoved = true;
        }
        pEmployee = pNext;
    }
    if (bRemoved && !this->m_employees.save()) {
        messages.addTail("Khong ghi duoc file " + HrSystem::EMPLOYEE_FILE_PATH);
        return false;
    }
    return true;
}

bool HrSystem::createDefaultAdmins(LinkedList<string>& messages) {
    bool bCreated = false;
    int iNumber = 1;
    while (this->m_admins.getSize() < HrSystem::DEFAULT_ADMIN_COUNT) {
        const string strName = HrSystem::DEFAULT_ADMIN_PREFIX + to_string(iNumber);
        iNumber++;
        if (this->isUsernameTaken(strName)) {
            continue;
        }
        this->m_admins.add(Admin(strName, HrSystem::DEFAULT_ADMIN_PASSWORD));
        messages.addTail("Da tao admin mac dinh: " + strName + " / " + HrSystem::DEFAULT_ADMIN_PASSWORD);
        bCreated = true;
    }

    if (bCreated) {
        if (!this->m_admins.save()) {
            messages.addTail("Khong ghi duoc file " + HrSystem::ADMIN_FILE_PATH);
            return false;
        }
    }

    return true;
}
