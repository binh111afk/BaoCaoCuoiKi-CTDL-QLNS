#pragma once
#include <string>
#include "Account.h"
#include <sstream>

using namespace std;

// Một đối tượng Employee được tạo ra khi mà chương trình nạp vào một tài khoản nhân viên
class Employee : public Account {
private:
    bool m_needsPasswordChange;

public:
    Employee(const string& username = "", const string& password = "",
             bool needsPasswordChange = false)
        : Account(username, password), m_needsPasswordChange(needsPasswordChange) {
    }

    // Mật khẩu của một tài khoản nhân viên
    static string defaultPassword() {
        return "111111";
    }

    // Tạo mới một tài khoản nhân viên (mật khẩu mặc định)
    static Employee createNew(const string& username) {
        return Employee(username, defaultPassword(), true);
    }

    // Nhập thông tin từ string line vào Employee out
    static bool fromLine(const string& line, Employee& out) {
        istringstream stream = istringstream(line);
        string username;
        string password;
        string flag;
        string extra;

        stream >> username >> password >> flag;
        if (!stream) {
            return false;
        }

        if (stream >> extra) {
            return false;
        }

        if (flag != "0" && flag != "1") {
            return false;
        }

        if (flag == "1") {
            out = Employee(username, password, true);
            return true;
        }

        out = Employee(username, password, false);

        return true;
    }

    // Trả về chuỗi thể hiện tên, mật khẩu, cờ đổi mật khẩu của tài khoản nhân viên
    string toLine() const override {
        string flag;
        if (m_needsPasswordChange) {
            flag = "1";
        } else {
            flag = "0";
        }

        return getUsername() + " " + getPassword() + " " + flag;
    }

    // Trả về vai trò của tài khoản nhân viên
    Role getRole() const override {
        return Role::EMPLOYEE;
    }

    // Tài khoản nhân viên nếu cần đổi mật khẩu thì trả về true
    bool needsPasswordChange() const {
        return m_needsPasswordChange;
    }

    // Đặt cờ đổi mật khẩu của tài khoản nhân viên
    void setNeedsPasswordChange(bool value) {
        m_needsPasswordChange = value;
    }
};
