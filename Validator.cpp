#include <cctype>
#include <vector>
#include "Validator.h"
#include "Util.h"

using namespace std;

const string Validator::ERROR_USERNAME = "Username dai 3-20 ky tu, chi gom chu, so, _ va bat dau bang chu";
const string Validator::ERROR_USERNAME_RESERVED = "Username trung ten danh rieng cua Windows";
const string Validator::ERROR_PASSWORD = "Mat khau dai 6-20 ky tu, khong co dau cach va chu co dau";
const string Validator::ERROR_FULL_NAME = "Ho ten 1-50 ky tu, chi gom chu khong dau va dau cach";
const string Validator::ERROR_ADDRESS = "Dia chi 1-100 ky tu, khong dung chu co dau";
const string Validator::ERROR_PHONE = "So dien thoai gom dung 10 chu so va bat dau bang 0";
const string Validator::ERROR_EMAIL = "Email khong hop le (vi du dung: ten@gmail.com)";

string Validator::checkUsername(const string& username) {
    if (username.length() < Validator::MIN_USERNAME_LENGTH || username.length() > Validator::MAX_USERNAME_LENGTH) {
        return Validator::ERROR_USERNAME;
    }

    if (!isalpha(static_cast<unsigned char>(username[0])) || !Validator::isAllUsernameChars(username)) {
        return Validator::ERROR_USERNAME;
    }

    if (Validator::isReservedName(Util::toLower(username))) {
        return Validator::ERROR_USERNAME_RESERVED;
    }
    return "";
}

string Validator::checkPassword(const string& password) {
    if (password.length() < Validator::MIN_PASSWORD_LENGTH || password.length() > Validator::MAX_PASSWORD_LENGTH) {
        return Validator::ERROR_PASSWORD;
    }

    if (!Validator::isAllCharsInRange(password, Validator::ASCII_FIRST_VISIBLE, Validator::ASCII_LAST_VISIBLE)) {
        return Validator::ERROR_PASSWORD;
    }
    return "";
}

string Validator::checkFullName(const string& fullName) {
    if (fullName.empty() || fullName.length() > Validator::MAX_FULL_NAME_LENGTH) {
        return Validator::ERROR_FULL_NAME;
    }

    if (!Validator::isAllLettersOrSpaces(fullName)) {
        return Validator::ERROR_FULL_NAME;
    }
    return "";
}

string Validator::checkAddress(const string& address) {
    if (address.empty() || address.length() > Validator::MAX_ADDRESS_LENGTH) {
        return Validator::ERROR_ADDRESS;
    }

    if (!Validator::isAllCharsInRange(address, Validator::ASCII_SPACE, Validator::ASCII_LAST_VISIBLE)) {
        return Validator::ERROR_ADDRESS;
    }
    return "";
}

string Validator::checkPhone(const string& phone) {
    if (phone.length() != Validator::PHONE_LENGTH || !Util::isAllDigits(phone)) {
        return Validator::ERROR_PHONE;
    }

    if (phone[0] != Validator::PHONE_FIRST_DIGIT) {
        return Validator::ERROR_PHONE;
    }
    return "";
}

string Validator::checkEmail(const string& email) {
    if (email.empty() || email.length() > Validator::MAX_EMAIL_LENGTH) {
        return Validator::ERROR_EMAIL;
    }

    if (!Validator::isAllCharsInRange(email, Validator::ASCII_FIRST_VISIBLE, Validator::ASCII_LAST_VISIBLE)) {
        return Validator::ERROR_EMAIL;
    }

    const size_t iAt = email.find('@');
    if (iAt == string::npos || iAt == 0 || email.find('@', iAt + 1) != string::npos) {
        return Validator::ERROR_EMAIL;
    }

    const size_t iDot = email.find('.', iAt + 1);
    if (iDot == string::npos || iDot == iAt + 1 || iDot == email.length() - 1) {
        return Validator::ERROR_EMAIL;
    }
    return "";
}

string Validator::checkField(const ProfileField field, const string& value) {
    switch (field) {
        case ProfileField::FULL_NAME:
            return Validator::checkFullName(value);

        case ProfileField::ADDRESS:
            return Validator::checkAddress(value);

        case ProfileField::PHONE:
            return Validator::checkPhone(value);

        case ProfileField::EMAIL:
            return Validator::checkEmail(value);

        default:
            return "";
    }
}

bool Validator::isAllCharsInRange(const string& text, const int minCode, const int maxCode) {
    for (size_t iIndex = 0; iIndex < text.length(); iIndex++) {
        const int iCode = static_cast<unsigned char>(text[iIndex]);
        if (iCode < minCode || iCode > maxCode) {
            return false;
        }
    }
    return true;
}

bool Validator::isAllUsernameChars(const string& text) {
    for (size_t iIndex = 0; iIndex < text.length(); iIndex++) {
        const char cLetter = text[iIndex];
        if (!isalnum(static_cast<unsigned char>(cLetter)) && cLetter != '_') {
            return false;
        }
    }
    return true;
}

bool Validator::isAllLettersOrSpaces(const string& text) {
    for (size_t iIndex = 0; iIndex < text.length(); iIndex++) {
        const char cLetter = text[iIndex];
        if (!isalpha(static_cast<unsigned char>(cLetter)) && cLetter != ' ') {
            return false;
        }
    }
    return true;
}

bool Validator::isReservedName(const string& lowerName) {
    const vector<string> reservedNames = {"con", "prn", "aux", "nul"};
    for (size_t iIndex = 0; iIndex < reservedNames.size(); iIndex++) {
        if (lowerName == reservedNames[iIndex]) {
            return true;
        }
    }

    for (int iNumber = 1; iNumber <= Validator::MAX_DEVICE_NUMBER; iNumber++) {
        if (lowerName == "com" + to_string(iNumber) || lowerName == "lpt" + to_string(iNumber)) {
            return true;
        }
    }
    return false;
}
