#pragma once
#include <string>
#include "Account.h"
#include "HrSystem.h"

// Điểm bắt đầu của chương trình: khởi tạo hệ thống, đăng nhập, vào menu theo vai trò rồi quay lại đăng nhập
class Application {
public:
    /**********************************************************
    * @Description Chạy toàn bộ chương trình
    *
    * @return 0 nếu kết thúc bình thường, 1 nếu không chuẩn bị được dữ liệu
    * @attention Chỉ gọi một lần, main chỉ gọi hàm này
    **********************************************************/
    int run();

private:
    /**********************************************************
    * @Description Màn hình đăng nhập: hỏi User và Pass cho tới khi đúng, người dùng để trống User, hoặc sai đủ MAX_FAILS lần
    *
    * @return true nếu đăng nhập đúng, accountName và role được ghi lại
    * @attention Trả về false nếu cần kết thúc chương trình
    **********************************************************/
    bool login(std::string& accountName, Role& role);

    // Số lần đăng nhập sai liên tiếp tối đa, sai đủ số lần này thì chương trình tự kết thúc
    static const int MAX_FAILS = 3;

    // Hệ thống duy nhất của chương trình, các menu mượn tham chiếu tới đối tượng này
    HrSystem m_system;
};
