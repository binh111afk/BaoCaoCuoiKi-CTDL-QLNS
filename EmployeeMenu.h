#pragma once
#include <string>
#include <vector>
#include "Menu.h"
#include "HrSystem.h"

using namespace std;

// Menu của nhân viên: xem thông tin tài khoản và đổi mật khẩu, nhân viên chỉ làm được trên tài khoản của chính mình
class EmployeeMenu : public Menu {
private:
    // Trả về 2 tên mục chức năng của nhân viên
    vector<string> getOptions() const override;

    // Gọi chức năng ứng với số choice (1 hoặc 2)
    void handleChoice(int choice) override;

    // Đọc hồ sơ của nhân viên đang đăng nhập rồi in ra
    void showMyInfo();

    // Đổi mật khẩu tự nguyện: xác nhận mật khẩu hiện tại rồi nhập mật khẩu mới hai lần
    void changePassword();

    // Hỏi mật khẩu mới hai lần, có lỗi thì in ra
    // Trả về true nếu mật khẩu mới hợp lệ và hai lần gõ khớp nhau, mật khẩu được ghi vào newPassword
    bool askNewPassword(string& newPassword);

    // Hệ thống dùng chung của chương trình, menu chỉ mượn chứ không sở hữu
    HrSystem& m_system;

    // Tên đăng nhập của nhân viên đang đăng nhập, mọi chức năng chỉ làm trên tài khoản này
    string m_username;

public:
    // Tạo menu cho nhân viên có tên đăng nhập username, tiêu đề menu hiện kèm username
    EmployeeMenu(HrSystem& system, const string& username);

    // Buộc đổi mật khẩu ở lần đăng nhập đầu, hỏi lại cho tới khi nhập được mật khẩu hợp lệ
    // Trả về true nếu mật khẩu đã được đổi và ghi vào file
    bool forcePasswordChange();
};
