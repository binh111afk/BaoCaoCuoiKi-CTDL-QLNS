#pragma once
#include <string>
#include <vector>

using namespace std;

// Bốn thông tin trong hồ sơ của một nhân viên, thứ tự cũng là thứ tự các dòng trong file [username].txt
enum class ProfileField { FULL_NAME, ADDRESS, PHONE, EMAIL };

// Hồ sơ của một nhân viên: họ tên, địa chỉ, số điện thoại, email
class UserProfile {
private:
    // Giá trị của 4 thông tin, đánh số theo ProfileField
    string m_values[4];

public:
    // Số lượng thông tin trong một hồ sơ
    static const int FIELD_COUNT = 4;

    // Trả giá trị của thông tin field
    string get(ProfileField field) const {
        return m_values[static_cast<int>(field)];
    }

    // Gán value cho thông tin field
    void set(ProfileField field, const string& value) {
        m_values[static_cast<int>(field)] = value;
    }

    // Trả tên hiển thị không dấu của thông tin
    static string labelOf(ProfileField field) {
        switch (field) {
            case ProfileField::FULL_NAME: return "Ho ten";
            case ProfileField::ADDRESS:   return "Dia chi";
            case ProfileField::PHONE:     return "So dien thoai";
            case ProfileField::EMAIL:     return "Email";
        }
        return "";
    }

    // Trả vector 4 chuỗi theo thứ tự
    vector<string> toLines() const {
        return {
            m_values[static_cast<int>(ProfileField::FULL_NAME)],
            m_values[static_cast<int>(ProfileField::ADDRESS)],
            m_values[static_cast<int>(ProfileField::PHONE)],
            m_values[static_cast<int>(ProfileField::EMAIL)]
        };
    }

    // Lấy 4 dòng đầu của lines gán vào out, trả false nếu ít hơn 4 dòng
    static bool fromLines(const vector<string>& lines, UserProfile& out) {
        if (lines.size() < 4) {
            return false;
        }
        
        out.set(ProfileField::FULL_NAME, lines[0]);
        out.set(ProfileField::ADDRESS, lines[1]);
        out.set(ProfileField::PHONE, lines[2]);
        out.set(ProfileField::EMAIL, lines[3]);
        
        return true;
    }
};