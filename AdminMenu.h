#pragma once
#include <string>
#include <vector>
#include "Menu.h"
#include "HrSystem.h"

using namespace std;

// Menu của admin: thêm, xóa, tìm, cập nhật và hiển thị thông tin nhân viên
class AdminMenu : public Menu {
private:
    // Trả về 5 tên mục chức năng của admin
    vector<string> getOptions() const override;

    // Gọi chức năng ứng với số choice (từ 1 tới 5)
    void handleChoice(int choice) override;

    // Hỏi username và 4 thông tin, kiểm tra từng ô rồi thêm nhân viên mới
    void addEmployee();

    // Hỏi username, hỏi xác nhận y/n rồi xóa nhân viên (dòng trong Employees.txt và file hồ sơ)
    void removeEmployee();

    // Hỏi username rồi in thông tin của đúng nhân viên đó
    void findEmployee();

    // Hỏi username rồi cho chọn từng thông tin để sửa, chọn Xong để quay về
    void updateEmployee();

    // In danh sách mọi nhân viên theo thứ tự username, mỗi người một dòng
    void showAllEmployees();

    // Hệ thống dùng chung của chương trình, menu chỉ mượn chứ không sở hữu
    HrSystem& m_system;

public:
    // Tạo menu cho admin có tên đăng nhập username, tiêu đề menu hiện kèm username
    AdminMenu(HrSystem& system, const string& username);
};
