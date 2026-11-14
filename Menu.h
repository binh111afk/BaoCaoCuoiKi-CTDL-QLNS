#pragma once
#include <string>
#include <vector>
#include "UserProfile.h"

using namespace std;

// Khung chung của menu: lớp con chỉ cần viết getOptions và handleChoice, vòng lặp menu đã có sẵn ở run
class Menu {
private:
    // Trả về tên các mục chức năng của menu theo thứ tự hiện ra (không gồm mục thoát)
    virtual vector<string> getOptions() const = 0;

    // Chạy chức năng ứng với số choice mà người dùng vừa chọn (đếm từ 1, không bao giờ là mục thoát)
    virtual void handleChoice(int choice) = 0;

    // Tiêu đề hiện trong khung sao ở đầu menu
    string m_title;

    // Chữ của mục thoát, luôn là mục cuối cùng của menu
    string m_exitLabel;

public:
    // title là tiêu đề trong khung sao, exitLabel là chữ của mục thoát (luôn nằm cuối danh sách)
    Menu(const string& title, const string& exitLabel);
    virtual ~Menu() {}

    // Lặp: hiện tiêu đề và danh sách mục, cho người dùng chọn, xử lý chức năng, cho tới khi chọn mục thoát
    void run();

    // In username và 4 thông tin của profile, mỗi thông tin một dòng
    static void printProfile(const string& username, const UserProfile& profile);
};
