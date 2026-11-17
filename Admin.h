#pragma once
#include <string>
#include "Account.h"

// Một đối tượng Admin được tạo ra khi chương trình nạp vào một tài khoản quản trị
class Admin : public Account {
public:
    /**********************************************************
    * @Description Tạo tài khoản admin với tên đăng nhập username và mật khẩu password
    *
    * @attention Không truyền tham số thì được admin rỗng để fromLine điền dữ liệu vào sau
    **********************************************************/
    Admin(const std::string& username = "", const std::string& password = "");

    /**********************************************************
    * @Description Nhập thông tin từ string line vào Admin out
    *
    * @return true nếu line có đúng 2 từ (tên đăng nhập và mật khẩu)
    * @attention Trả về false thì out không bị đổi
    **********************************************************/
    static bool fromLine(const std::string& line, Admin& out);

    /**********************************************************
    * @Description Tạo chuỗi thể hiện tên và mật khẩu của tài khoản admin
    *
    * @return Một dòng của file Administrators.txt
    **********************************************************/
    std::string toLine() const override;

    /**********************************************************
    * @Description Lấy vai trò của tài khoản admin
    *
    * @return Role::ADMIN
    **********************************************************/
    Role getRole() const override;
};
