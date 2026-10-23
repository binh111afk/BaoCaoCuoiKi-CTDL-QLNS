#pragma once
#include <string>
#include "Util.h"
#include "UserProfile.h"

class Validator {
public:
    static std::string checkUsername(const std::string& s) {
        return "";
    }

    static std::string checkPassword(const std::string& s) {
        return "";
    }

    static std::string checkFullName(const std::string& s) {
        return "";
    }

    static std::string checkAddress(const std::string& s) {
        return "";
    }

    static std::string checkPhone(const std::string& s) {
        return "";
    }

    static std::string checkEmail(const std::string& s) {
        return "";
    }

    static std::string checkField(ProfileField field, const std::string& value) {
        return "";
    }
};
