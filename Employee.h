#pragma once
#include <string>
#include "Account.h"

// Một đối tượng Employee được tạo ra khi mà chương trình nạp vào một tài khoản nhân viên
class Employee : public Account {
public:
    /**********************************************************
    * @Description Tạo tài khoản nhân viên với tên đăng nhập username, mật khẩu password và cờ needsPasswordChange
    *
    * @attention Không truyền tham số thì được nhân viên rỗng để fromLine điền dữ liệu vào sau
    **********************************************************/
    Employee(const std::string& username = "", const std::string& password = "",
             const bool needsPasswordChange = false);

    /**********************************************************
    * @Description Lấy mật khẩu mặc định của một tài khoản nhân viên mới
    *
    * @return Mật khẩu mặc định
    **********************************************************/
    static std::string defaultPassword();

    /**********************************************************
    * @Description Tạo mới một tài khoản nhân viên với mật khẩu mặc định
    *
    * @return Tài khoản nhân viên mới, có cờ bắt đổi mật khẩu ở lần đăng nhập đầu
    **********************************************************/
    static Employee createNew(const std::string& username);

    /**********************************************************
    * @Description Nhập thông tin từ string line vào Employee out
    *
    * @return true nếu line có đúng 3 từ (tên, mật khẩu, cờ đổi mật khẩu 0 hoặc 1)
    **********************************************************/
    static bool fromLine(const std::string& line, Employee& out);

    /**********************************************************
    * @Description Tạo chuỗi thể hiện tên, mật khẩu, cờ đổi mật khẩu của tài khoản nhân viên
    *
    * @return Một dòng của file Employees.txt
    **********************************************************/
    std::string toLine() const override;

    /**********************************************************
    * @Description Lấy vai trò của tài khoản nhân viên
    *
    * @return Role::EMPLOYEE
    **********************************************************/
    Role getRole() const override;

    /**********************************************************
    * @Description Kiểm tra tài khoản nhân viên có cần đổi mật khẩu hay không
    *
    * @return true nếu cần đổi mật khẩu
    **********************************************************/
    bool needsPasswordChange() const;

    /**********************************************************
    * @Description Đặt cờ đổi mật khẩu của tài khoản nhân viên thành value
    **********************************************************/
    void setNeedsPasswordChange(const bool value);

private:
    // Mật khẩu mặc định của tài khoản nhân viên mới
    static const std::string DEFAULT_PASSWORD;

    // Giá trị của cột cờ trong file Employees.txt khi nhân viên cần đổi mật khẩu
    static const char* const FLAG_NEEDED;

    // Giá trị của cột cờ trong file Employees.txt khi nhân viên không cần đổi mật khẩu
    static const char* const FLAG_NOT_NEEDED;

    // Bằng true nếu nhân viên phải đổi mật khẩu ở lần đăng nhập tới
    bool m_bNeedsPasswordChange;
};
