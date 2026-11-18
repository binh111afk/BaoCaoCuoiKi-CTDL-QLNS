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

LinkedList<string> UserProfile::toLines() const {
    LinkedList<string> lines;
    for (int iField = 0; iField < UserProfile::FIELD_COUNT; iField++) {
        lines.addTail(this->m_strValues[iField]);
    }
    return lines;
}

bool UserProfile::fromLines(const LinkedList<string>& lines, UserProfile& out) {
    if (lines.getSize() < UserProfile::FIELD_COUNT) {
        return false;
    }

    Node<string>* pLine = lines.getHead();
    for (int iField = 0; iField < UserProfile::FIELD_COUNT; iField++) {
        out.m_strValues[iField] = pLine->getData();
        pLine = pLine->getNext();
    }
    return true;
}
