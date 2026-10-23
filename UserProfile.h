#pragma once
#include <string>
#include <vector>

enum class ProfileField { FULL_NAME, ADDRESS, PHONE, EMAIL };

class UserProfile {
private:
    std::string m_values[4];

public:
    static const int FIELD_COUNT = 4;

    std::string get(ProfileField field) const {
        return "";
    }

    void set(ProfileField field, const std::string& value) {}

    static std::string labelOf(ProfileField field) {
        return "";
    }

    std::vector<std::string> toLines() const {
        return std::vector<std::string>();
    }

    static bool fromLines(const std::vector<std::string>& lines, UserProfile& out) {
        return false;
    }
};
