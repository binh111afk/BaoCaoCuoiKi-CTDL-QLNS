#pragma once
#include <string>

// Vai trò của một tài khoản: quản trị viên hoặc nhân viên
enum class Role { ADMIN, EMPLOYEE };

// Lớp cha của mọi tài khoản, chỉ tạo được Admin hoặc Employee
class Account {
public:
    /**********************************************************
    * @Description Tạo tài khoản với tên đăng nhập username và mật khẩu password
    *
    * @attention Chỉ Admin và Employee gọi được vì Account có hàm thuần ảo
    **********************************************************/
    Account(const std::string& username, const std::string& password);

    virtual ~Account() = default;

    /**********************************************************
    * @Description Lấy tên đăng nhập của một tài khoản
    *
    * @return Tên đăng nhập, đúng chữ hoa chữ thường như lúc tạo
    **********************************************************/
    std::string getUsername() const;

    /**********************************************************
    * @Description Lấy mật khẩu của một tài khoản
    *
    * @return Mật khẩu nguyên văn
    * @attention Chỉ dùng khi ghi file, muốn kiểm mật khẩu thì dùng checkPassword
    **********************************************************/
    std::string getPassword() const;

    /**********************************************************
    * @Description So name với tên đăng nhập của tài khoản mà không phân biệt hoa thường
    *
    * @return true nếu name giống tên đăng nhập của tài khoản
    **********************************************************/
    bool matchesUsername(const std::string& name) const;

    /**********************************************************
    * @Description Kiểm tra xem password có đúng với mật khẩu của Account hay không
    *
    * @return true nếu password giống hệt mật khẩu (có phân biệt hoa thường)
    **********************************************************/
    bool checkPassword(const std::string& password) const;

    /**********************************************************
    * @Description Đổi mật khẩu của tài khoản thành newPassword
    *
    * @attention Chỉ đổi trong bộ nhớ, muốn lưu thì nơi gọi phải ghi lại file
    **********************************************************/
    void setPassword(const std::string& newPassword);

    /**********************************************************
    * @Description Tạo một dòng chữ chứa dữ liệu của tài khoản để ghi vào file
    *
    * @return Dòng chữ không có ký tự xuống dòng
    **********************************************************/
    virtual std::string toLine() const = 0;

    /**********************************************************
    * @Description Lấy vai trò của tài khoản
    *
    * @return Role::ADMIN hoặc Role::EMPLOYEE tùy lớp con
    **********************************************************/
    virtual Role getRole() const = 0;

private:
    // Tên đăng nhập, giữ đúng chữ hoa chữ thường như lúc tạo
    std::string m_strUsername;

    // Mật khẩu, lưu nguyên văn như trong file
    std::string m_strPassword;
};
