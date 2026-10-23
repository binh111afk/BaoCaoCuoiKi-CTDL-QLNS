#pragma once
#include <string>
#include "Util.h"
#include "UserProfile.h"

using namespace std;

class Validator {
public:
    static string checkUsername(const string& s) {
        return "";
    }

    static string checkPassword(const string& s) {
        return "";
    }

    static string checkFullName(const string& s) {
        return "";
    }

    static string checkAddress(const string& s) {
        return "";
    }

    static string checkPhone(const string& s) {
        return "";
    }

    static string checkEmail(const string& s) {
        return "";
    }

    static string checkField(ProfileField field, const string& value) {
        return "";
    }
};
