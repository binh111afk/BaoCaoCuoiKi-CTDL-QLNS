#include "UserProfile.h"

using namespace std;

string UserProfile::get(const ProfileField field) const {
    return this->m_strValues[static_cast<int>(field)];
}

void UserProfile::set(const ProfileField field, const string& value) {
    this->m_strValues[static_cast<int>(field)] = value;
}

string UserProfile::labelOf(const ProfileField field) {
    switch (field) {
        case ProfileField::FULL_NAME:
            return "Ho ten";

        case ProfileField::ADDRESS:
            return "Dia chi";

        case ProfileField::PHONE:
            return "So dien thoai";

        case ProfileField::EMAIL:
            return "Email";

        default:
            return "";
    }
}

vector<string> UserProfile::toLines() const {
    vector<string> lines;
    for (int iField = 0; iField < UserProfile::FIELD_COUNT; iField++) {
        lines.push_back(this->m_strValues[iField]);
    }
    return lines;
}

bool UserProfile::fromLines(const vector<string>& lines, UserProfile& out) {
    if (lines.size() < static_cast<size_t>(UserProfile::FIELD_COUNT)) {
        return false;
    }

    for (int iField = 0; iField < UserProfile::FIELD_COUNT; iField++) {
        out.m_strValues[iField] = lines[static_cast<size_t>(iField)];
    }
    return true;
}
