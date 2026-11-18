#pragma once
#include <string>
#include "LinkedList.h"
#include "UserProfile.h"

// Khung chung của menu: lớp con chỉ cần viết getOptions và handleChoice, vòng lặp menu đã có sẵn ở run
class Menu {
public:
    /**********************************************************
    * @Description Tạo menu với tiêu đề title và chữ của mục thoát exitLabel
    *
    * @attention Chỉ lớp con gọi được vì Menu có hàm thuần ảo
    **********************************************************/
    Menu(const std::string& title, const std::string& exitLabel);

    virtual ~Menu() = default;

    /**********************************************************
    * @Description Lặp: hiện tiêu đề và danh sách mục, cho người dùng chọn, xử lý chức năng
    *
    * @attention Mục thoát luôn nằm cuối danh sách, chọn mục thoát thì trả về
    * @attention Sau mỗi chức năng có chờ một phím để người dùng kịp đọc kết quả
    **********************************************************/
    void run();

    /**********************************************************
    * @Description In username và 4 thông tin của profile, mỗi thông tin một dòng
    **********************************************************/
    static void printProfile(const std::string& username, const UserProfile& profile);

protected:
    // Chữ của mục thoát dùng cho menu đã đăng nhập (đăng xuất)
    static const std::string LOGOUT_LABEL;

private:
    /**********************************************************
    * @Description Lấy tên các mục chức năng của menu theo thứ tự hiện ra
    *
    * @return Danh sách tên mục, không gồm mục thoát
    * @attention Mục thứ i (đếm từ 0) ứng với lựa chọn i + 1
    **********************************************************/
    virtual LinkedList<std::string> getOptions() const = 0;

    /**********************************************************
    * @Description Chạy chức năng ứng với số choice mà người dùng vừa chọn
    *
    * @attention choice đếm từ 1 và không bao giờ là mục thoát
    **********************************************************/
    virtual void handleChoice(const int choice) = 0;

    // Tiêu đề hiện trong khung sao ở đầu menu
    std::string m_strTitle;

    // Chữ của mục thoát, luôn là mục cuối cùng của menu
    std::string m_strExitLabel;
};
