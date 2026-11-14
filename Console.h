#pragma once
#include <string>
#include <vector>

using namespace std;

// Lớp duy nhất đọc bàn phím và in ra màn hình, mọi thứ phụ thuộc console của Windows đều nằm ở đây
class Console {
public:
    // Mã màu chữ: thường, tiêu đề và cảnh báo (vàng), lời nhắc nhập liệu (xanh lá), báo thành công (xanh ngọc), báo lỗi (đỏ), mục đang chọn (nền sáng)
    static const int COLOR_NORMAL   = 7;
    static const int COLOR_TITLE    = 14;
    static const int COLOR_LABEL    = 10;
    static const int COLOR_SUCCESS  = 11;
    static const int COLOR_ERROR    = 12;
    static const int COLOR_SELECTED = 112;

    // Đặt màu chữ của console thành color, các chữ in sau đó mang màu này
    static void setColor(int color);

    // In text màu color kèm xuống dòng, rồi trả màu về COLOR_NORMAL
    static void printLine(const string& text, int color = COLOR_NORMAL);

    // In 3 dòng màu vàng: hàng dấu *, dòng tiêu đề căn giữa, hàng dấu *
    static void printTitle(const string& title);

    // In message màu xanh ngọc để báo thành công
    static void printSuccess(const string& message);

    // In message màu đỏ để báo lỗi
    static void printError(const string& message);

    // In prompt rồi đọc cả dòng người dùng gõ, trả về dòng đã bỏ khoảng trắng đầu cuối
    static string readLine(const string& prompt);

    // In prompt rồi đọc mật khẩu, mỗi ký tự gõ vào hiện thành dấu *
    static string readPassword(const string& prompt);

    // In các mục trong items, người dùng chọn bằng mũi tên lên xuống rồi Enter
    // Trả về số thứ tự của mục đã chọn (đếm từ 1), startAt là mục được chọn sẵn lúc đầu
    static int chooseOption(const vector<string>& items, int startAt = 1);

    // Hỏi question kèm (y/n), trả về true nếu người dùng gõ y hoặc Y
    static bool confirm(const string& question);

    // In lời nhắc rồi đứng chờ tới khi người dùng nhấn một phím
    static void pause();

    // Xóa trống màn hình và đưa con trỏ về góc trên bên trái
    static void clearScreen();
};
