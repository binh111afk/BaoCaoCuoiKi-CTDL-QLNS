#pragma once
#include <string>
#include "Util.h"

using namespace std;

// Vai trò của một tài khoản: quản trị viên hoặc nhân viên
enum class Role { ADMIN, EMPLOYEE };

// Lớp cha của mọi tài khoản, chỉ tạo được Admin hoặc Employee
class Account {
private:
    // Tên đăng nhập, giữ đúng chữ hoa chữ thường như lúc tạo
    string m_username;

    // Mật khẩu, lưu nguyên văn như trong file
    string m_password;

public:
    // Tạo tài khoản với tên đăng nhập username và mật khẩu password (chỉ Admin và Employee gọi được)
    Account(const string& username, const string& password)
        : m_username(username), m_password(password) {
    }
    virtual ~Account() {}

    // Trả về tên đăng nhập của một tài khoản
    string getUsername() const {
        return m_username;
    }

    // Trả về mật khẩu của một tài khoản (chỉ dùng khi ghi file, kiểm mật khẩu thì dùng checkPassword)
    string getPassword() const {
        return m_password;
    }

    // Trả về true nếu name giống tên đăng nhập của tài khoản (không phân biệt hoa thường)
    bool matchesUsername(const string& name) const {
        return Util::equalsIgnoreCase(m_username, name);
    }

    // Kiểm tra xem password có đúng với mật khẩu của Account hay không (có phân biệt hoa thường)
    // Nếu đúng thì trả về true
    bool checkPassword(const string& password) const {
        return m_password == password;
    }

    // Đổi mật khẩu của tài khoản thành newPassword, chỉ đổi trong bộ nhớ
    void setPassword(const string& newPassword) {
        m_password = newPassword;
    }

    // Trả về một dòng chữ chứa dữ liệu của tài khoản để ghi vào file
    virtual string toLine() const = 0;

    // Trả về vai trò của tài khoản
    virtual Role getRole() const = 0;
};
