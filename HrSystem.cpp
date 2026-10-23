#include "HrSystem.h"
#include "Util.h"
#include "Validator.h"

HrSystem::HrSystem() {}

bool HrSystem::initialize(std::vector<std::string>& messages) {
    return false;
}

bool HrSystem::login(const std::string& username, const std::string& password,
                     Role& role, std::string& accountName) {
    return false;
}

bool HrSystem::needsPasswordChange(const std::string& username) {
    return false;
}

bool HrSystem::verifyPassword(const std::string& username, const std::string& password) {
    return false;
}

std::string HrSystem::checkNewUsername(const std::string& username) {
    return "";
}

std::string HrSystem::checkNewPassword(const std::string& username, const std::string& newPassword) {
    return "";
}

std::string HrSystem::addEmployee(const std::string& username, const UserProfile& profile) {
    return "";
}

std::string HrSystem::removeEmployee(const std::string& username) {
    return "";
}

std::string HrSystem::findEmployee(const std::string& username, UserProfile& profile) {
    return "";
}

std::string HrSystem::updateField(const std::string& username, ProfileField field,
                                  const std::string& value) {
    return "";
}

void HrSystem::listEmployees(std::vector<std::string>& usernames) {}

std::string HrSystem::changePassword(const std::string& username, const std::string& newPassword) {
    return "";
}

bool HrSystem::isUsernameTaken(const std::string& username) const {
    return false;
}

std::string HrSystem::profilePath(const std::string& username) {
    return "";
}
