#pragma once
#include <string>
#include "Account.h"
#include "HrSystem.h"

using namespace std;

// Điểm bắt đầu của chương trình: khởi tạo hệ thống, đăng nhập, vào menu theo vai trò rồi quay lại đăng nhập
class Application {
private:
    // Số lần đăng nhập sai liên tiếp tối đa, sai đủ số lần này thì chương trình tự kết thúc
    static const int MAX_FAILS = 3;

    // Màn hình đăng nhập: hỏi User và Pass cho tới khi đúng, người dùng để trống User, hoặc sai đủ MAX_FAILS lần
    // Trả về true nếu đăng nhập đúng, accountName và role được ghi lại
    // Trả về false nếu cần kết thúc chương trình
    bool login(string& accountName, Role& role);

    // Hệ thống duy nhất của chương trình, các menu mượn tham chiếu tới đối tượng này
    HrSystem m_system;

public:
    // Chạy toàn bộ chương trình, trả về 0 nếu kết thúc bình thường, 1 nếu không chuẩn bị được dữ liệu
    int run();
};
