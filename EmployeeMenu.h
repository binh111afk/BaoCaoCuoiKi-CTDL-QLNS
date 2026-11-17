#pragma once
#include <string>
#include <vector>
#include "Menu.h"
#include "HrSystem.h"

// Menu của nhân viên: xem thông tin tài khoản và đổi mật khẩu, nhân viên chỉ làm được trên tài khoản của chính mình
class EmployeeMenu : public Menu {
public:
    /**********************************************************
    * @Description Tạo menu cho nhân viên có tên đăng nhập username
    *
    * @attention Tiêu đề menu hiện kèm username, system là hệ thống dùng chung của chương trình
    **********************************************************/
    EmployeeMenu(HrSystem& system, const std::string& username);

    /**********************************************************
    * @Description Buộc đổi mật khẩu ở lần đăng nhập đầu, hỏi lại cho tới khi nhập được mật khẩu hợp lệ
    *
    * @return true nếu mật khẩu đã được đổi và ghi vào file
    * @attention Kết thúc bằng một lần chờ phím để người dùng kịp đọc kết quả
    **********************************************************/
    bool forcePasswordChange();

private:
    // Số thứ tự của từng chức năng trong menu nhân viên
    enum MenuChoice {
        CHOICE_SHOW_INFO = 1,
        CHOICE_CHANGE_PASSWORD = 2
    };

    /**********************************************************
    * @Description Lấy tên 2 mục chức năng của nhân viên
    *
    * @return Danh sách 2 tên mục
    **********************************************************/
    std::vector<std::string> getOptions() const override;

    /**********************************************************
    * @Description Gọi chức năng ứng với số choice (1 hoặc 2)
    **********************************************************/
    void handleChoice(const int choice) override;

    /**********************************************************
    * @Description Đọc hồ sơ của nhân viên đang đăng nhập rồi in ra
    *
    * @attention Thiếu file hồ sơ thì báo lỗi
    **********************************************************/
    void showMyInfo();

    /**********************************************************
    * @Description Đổi mật khẩu tự nguyện: xác nhận mật khẩu hiện tại rồi nhập mật khẩu mới hai lần
    **********************************************************/
    void changePassword();

    /**********************************************************
    * @Description Hỏi mật khẩu mới hai lần, có lỗi thì in ra
    *
    * @return true nếu mật khẩu mới hợp lệ và hai lần gõ khớp nhau
    * @attention Mật khẩu hợp lệ được ghi vào newPassword
    **********************************************************/
    bool askNewPassword(std::string& newPassword);

    // Hệ thống dùng chung của chương trình, menu chỉ mượn chứ không sở hữu
    HrSystem& m_system;

    // Tên đăng nhập của nhân viên đang đăng nhập, mọi chức năng chỉ làm trên tài khoản này
    std::string m_strUsername;
};
