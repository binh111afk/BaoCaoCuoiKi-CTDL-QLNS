#pragma once
#include <cctype>
#include <string>
#include <vector>
#include "Util.h"
#include "UserProfile.h"

using namespace std;

// Kiểm tra định dạng dữ liệu nhập, mỗi hàm trả về chuỗi rỗng nếu hợp lệ, không thì trả về câu mô tả lỗi
class Validator {
public:
    // Kiểm s có dùng được làm username không: 3-20 ký tự, chỉ gồm chữ không dấu, số và _, bắt đầu bằng chữ, không trùng tên file cấm của Windows
    static string checkUsername(const string& s) {
        if (s.length() < 3 || s.length() > 20) {
            return "Username dai 3-20 ky tu, chi gom chu, so, _ va bat dau bang chu";
        }

        if (!isalpha(static_cast<unsigned char>(s[0]))) {
            return "Username dai 3-20 ky tu, chi gom chu, so, _ va bat dau bang chu";
        }

        for (size_t i = 0; i < s.length(); i++) {
            if (!isalnum(static_cast<unsigned char>(s[i])) && s[i] != '_') {
                return "Username dai 3-20 ky tu, chi gom chu, so, _ va bat dau bang chu";
            }
        }

        vector<string> reserved = {"con", "prn", "aux", "nul"};
        for (int number = 1; number <= 9; number++) {
            reserved.push_back("com" + to_string(number));
            reserved.push_back("lpt" + to_string(number));
        }

        string lower = Util::toLower(s);
        for (size_t i = 0; i < reserved.size(); i++) {
            if (lower == reserved[i]) {
                return "Username trung ten danh rieng cua Windows";
            }
        }
        return "";
    }

    // Kiểm s có dùng được làm mật khẩu không: 6-20 ký tự, mỗi ký tự có mã từ 33 đến 126
    static string checkPassword(const string& s) {
        if (s.length() < 6 || s.length() > 20) {
            return "Mat khau dai 6-20 ky tu, khong co dau cach va chu co dau";
        }

        for (size_t i = 0; i < s.length(); i++) {
            int code = static_cast<unsigned char>(s[i]);
            if (code < 33 || code > 126) {
                return "Mat khau dai 6-20 ky tu, khong co dau cach va chu co dau";
            }
        }
        return "";
    }

    // Kiểm s có dùng được làm họ tên không: 1-50 ký tự, chỉ gồm chữ không dấu và dấu cách
    static string checkFullName(const string& s) {
        if (s.empty() || s.length() > 50) {
            return "Ho ten 1-50 ky tu, chi gom chu khong dau va dau cach";
        }

        for (size_t i = 0; i < s.length(); i++) {
            if (!isalpha(static_cast<unsigned char>(s[i])) && s[i] != ' ') {
                return "Ho ten 1-50 ky tu, chi gom chu khong dau va dau cach";
            }
        }
        return "";
    }

    // Kiểm s có dùng được làm địa chỉ không: 1-100 ký tự, mỗi ký tự có mã từ 32 đến 126
    static string checkAddress(const string& s) {
        if (s.empty() || s.length() > 100) {
            return "Dia chi 1-100 ky tu, khong dung chu co dau";
        }

        for (size_t i = 0; i < s.length(); i++) {
            int code = static_cast<unsigned char>(s[i]);
            if (code < 32 || code > 126) {
                return "Dia chi 1-100 ky tu, khong dung chu co dau";
            }
        }
        return "";
    }

    // Kiểm s có dùng được làm số điện thoại không: đúng 10 chữ số và bắt đầu bằng 0
    static string checkPhone(const string& s) {
        if (s.length() != 10 || !Util::isAllDigits(s) || s[0] != '0') {
            return "So dien thoai gom dung 10 chu so va bat dau bang 0";
        }
        return "";
    }

    // Kiểm s có dùng được làm email không: dạng ten@ten-mien.duoi, tối đa 50 ký tự, không có dấu cách
    static string checkEmail(const string& s) {
        string error = "Email khong hop le (vi du dung: ten@gmail.com)";

        if (s.empty() || s.length() > 50) {
            return error;
        }

        for (size_t i = 0; i < s.length(); i++) {
            int code = static_cast<unsigned char>(s[i]);
            if (code < 33 || code > 126) {
                return error;
            }
        }

        size_t at = s.find('@');
        if (at == string::npos || at == 0) {
            return error;
        }

        if (s.find('@', at + 1) != string::npos) {
            return error;
        }

        size_t dot = s.find('.', at + 1);
        if (dot == string::npos || dot == at + 1 || dot == s.length() - 1) {
            return error;
        }
        return "";
    }

    // Kiểm value có hợp lệ cho thông tin field không, bằng cách gọi hàm kiểm tương ứng
    static string checkField(ProfileField field, const string& value) {
        switch (field) {
            case ProfileField::FULL_NAME: return checkFullName(value);
            case ProfileField::ADDRESS:   return checkAddress(value);
            case ProfileField::PHONE:     return checkPhone(value);
            case ProfileField::EMAIL:     return checkEmail(value);
        }
        return "";
    }
};
