#include "HrSystem.h"
#include "Util.h"
#include "Validator.h"

HrSystem::HrSystem() {}

bool HrSystem::initialize(vector<string>& messages) {
    return false;
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
