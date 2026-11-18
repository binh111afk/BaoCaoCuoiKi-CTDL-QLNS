#pragma once
#include <string>
#include "LinkedList.h"
#include "Menu.h"
#include "HrSystem.h"

// Menu của admin: thêm, xóa, tìm, cập nhật và hiển thị thông tin nhân viên
class AdminMenu : public Menu {
public:
    /**********************************************************
    * @Description Tạo menu cho admin có tên đăng nhập username
    *
    * @attention Tiêu đề menu hiện kèm username, system là hệ thống dùng chung của chương trình
    **********************************************************/
    AdminMenu(HrSystem& system, const std::string& username);

private:
    // Số thứ tự của từng chức năng trong menu admin
    enum MenuChoice {
        CHOICE_ADD = 1,
        CHOICE_REMOVE = 2,
        CHOICE_FIND = 3,
        CHOICE_UPDATE = 4,
        CHOICE_SHOW_ALL = 5
    };

    /**********************************************************
    * @Description Lấy tên 5 mục chức năng của admin
    *
    * @return Danh sách 5 tên mục
    **********************************************************/
    LinkedList<std::string> getOptions() const override;

    /**********************************************************
    * @Description Gọi chức năng ứng với số choice (từ 1 tới 5)
    **********************************************************/
    void handleChoice(const int choice) override;

    /**********************************************************
    * @Description Hỏi username và 4 thông tin, kiểm tra từng ô rồi thêm nhân viên mới
    *
    * @attention Gặp lỗi thì in lỗi rồi dừng, không có gì thay đổi
    **********************************************************/
    void addEmployee();

    /**********************************************************
    * @Description Hỏi username, hỏi xác nhận y/n rồi xóa nhân viên
    *
    * @attention Xóa cả dòng trong Employees.txt và file hồ sơ, chỉ xóa khi gõ y hoặc Y
    **********************************************************/
    void removeEmployee();

    /**********************************************************
    * @Description Hỏi username rồi in thông tin của đúng nhân viên đó
    *
    * @attention Tìm theo đúng username, không tìm một phần
    **********************************************************/
    void findEmployee();

    /**********************************************************
    * @Description Hỏi username rồi cho chọn từng thông tin để sửa
    *
    * @attention Chọn mục Xong để quay về, mỗi thay đổi được ghi file ngay
    **********************************************************/
    void updateEmployee();

    /**********************************************************
    * @Description In danh sách mọi nhân viên theo thứ tự username, mỗi người một dòng
    *
    * @attention Chưa có nhân viên nào thì báo
    **********************************************************/
    void showAllEmployees();

    // Hệ thống dùng chung của chương trình, menu chỉ mượn chứ không sở hữu
    HrSystem& m_system;
};
