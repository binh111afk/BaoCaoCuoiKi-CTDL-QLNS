#pragma once
#include <string>
#include <vector>

using namespace std;

enum class ProfileField { FULL_NAME, ADDRESS, PHONE, EMAIL };

class UserProfile {
private:
    string m_values[4];

public:
    static const int FIELD_COUNT = 4;

    string get(ProfileField field) const {
        return "";
    }

    void set(ProfileField field, const string& value) {}

    static string labelOf(ProfileField field) {
        return "";
    }

    vector<string> toLines() const {
        return vector<string>();
    }

    static bool fromLines(const vector<string>& lines, UserProfile& out) {
        return false;
    }
};
