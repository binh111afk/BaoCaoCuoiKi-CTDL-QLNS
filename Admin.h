#pragma once
#include <string>
#include <sstream>
#include "Account.h"

using namespace std;

// Một đối tượng Admin được tạo ra khi chương trình nạp vào một tài khoản quản trị
class Admin : public Account {
public:
    // Tạo tài khoản admin, không truyền tham số thì được admin rỗng để fromLine điền dữ liệu vào sau
    Admin(const string& username = "", const string& password = "")
        : Account(username, password) {
    }

    // Nhập thông tin từ string line vào Admin out, trả về false nếu line không đúng 2 từ
    static bool fromLine(const string& line, Admin& out) {
        istringstream stream = istringstream(line);
        string username;
        string password;
        string extra;

        stream >> username >> password;
        if (!stream) {
            return false;
        }

        if (stream >> extra) {
            return false;
        }

        out = Admin(username, password);
        return true;
    }

    // Trả về chuỗi thể hiện tên và mật khẩu của tài khoản admin
    string toLine() const override {
        return getUsername() + " " + getPassword();
    }

    // Trả về vai trò của tài khoản admin
    Role getRole() const override {
        return Role::ADMIN;
    }
};
