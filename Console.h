#pragma once
#include <cstddef>
#include <string>
#include "LinkedList.h"

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

    /**********************************************************
    * @Description Đặt màu chữ của console thành color, các chữ in sau đó mang màu này
    *
    * @attention color là một trong các hằng COLOR_
    **********************************************************/
    static void setColor(const int color);

    /**********************************************************
    * @Description In text màu color kèm xuống dòng, rồi trả màu về COLOR_NORMAL
    **********************************************************/
    static void printLine(const std::string& text, const int color = COLOR_NORMAL);

    /**********************************************************
    * @Description In 3 dòng màu vàng: hàng dấu *, dòng tiêu đề căn giữa, hàng dấu *
    *
    * @attention title nên ngắn hơn 36 ký tự
    **********************************************************/
    static void printTitle(const std::string& title);

    /**********************************************************
    * @Description In message màu xanh ngọc để báo thành công
    **********************************************************/
    static void printSuccess(const std::string& message);

    /**********************************************************
    * @Description In message màu đỏ để báo lỗi
    **********************************************************/
    static void printError(const std::string& message);

    /**********************************************************
    * @Description In prompt rồi đọc cả dòng người dùng gõ
    *
    * @return Dòng đã nhập, đã bỏ khoảng trắng đầu cuối
    * @attention Đọc thất bại thì trả về chuỗi rỗng
    **********************************************************/
    static std::string readLine(const std::string& prompt);

    /**********************************************************
    * @Description In prompt rồi đọc mật khẩu, mỗi ký tự gõ vào hiện thành dấu *
    *
    * @return Mật khẩu đã gõ
    * @attention Backspace xóa ký tự cuối, Enter kết thúc
    **********************************************************/
    static std::string readPassword(const std::string& prompt);

    /**********************************************************
    * @Description In các mục trong items, người dùng chọn bằng mũi tên lên xuống rồi Enter
    *
    * @return Số thứ tự của mục đã chọn (đếm từ 1)
    * @attention startAt là mục được chọn sẵn lúc đầu
    * @attention items có từ 1 đến 15 mục, con trỏ phải đang ở đầu một dòng
    **********************************************************/
    static int chooseOption(const LinkedList<std::string>& items, const int startAt = 1);

    /**********************************************************
    * @Description Hỏi question kèm (y/n) rồi đọc một dòng
    *
    * @return true nếu người dùng gõ y hoặc Y
    **********************************************************/
    static bool confirm(const std::string& question);

    /**********************************************************
    * @Description In lời nhắc rồi đứng chờ tới khi người dùng nhấn một phím
    **********************************************************/
    static void pause();

    /**********************************************************
    * @Description Xóa trống màn hình và đưa con trỏ về góc trên bên trái
    **********************************************************/
    static void clearScreen();

private:
    /**********************************************************
    * @Description In từng mục của items thành một dòng, mục thứ selected có tiền tố "> " và nền sáng
    *
    * @attention selected đếm từ 1
    **********************************************************/
    static void printOptions(const LinkedList<std::string>& items, const int selected);

    /**********************************************************
    * @Description Đọc một phím trong lúc chọn mục: Enter để chốt, mũi tên để dời mục đang chọn
    *
    * @return true nếu người dùng nhấn Enter
    * @attention selected được cập nhật khi người dùng nhấn mũi tên
    **********************************************************/
    static bool readSelectionKey(int& selected, const int count);

    /**********************************************************
    * @Description Dời mục đang chọn lên hoặc xuống theo mã mũi tên arrowKey
    *
    * @attention Dời quá mục đầu hoặc mục cuối thì quay vòng sang đầu kia
    **********************************************************/
    static void moveSelection(const int arrowKey, int& selected, const int count);

    /**********************************************************
    * @Description Xử lý một phím key trong lúc nhập mật khẩu: thêm ký tự, xóa ký tự cuối hoặc bỏ qua
    **********************************************************/
    static void applyPasswordKey(const int key, std::string& password);

    /**********************************************************
    * @Description Xóa ký tự cuối của password và xóa một dấu * trên màn hình
    *
    * @attention password rỗng thì không làm gì
    **********************************************************/
    static void removeLastPasswordChar(std::string& password);

    // Độ rộng phần chữ bên trong khung tiêu đề, và số dấu viền hai bên
    static const std::size_t TITLE_WIDTH = 36;
    static const std::size_t TITLE_BORDER_SIDES = 2;
    static const char TITLE_BORDER = '*';

    // Ký tự hiện lên màn hình thay cho mỗi ký tự mật khẩu
    static const char PASSWORD_MASK = '*';

    // Số thứ tự của mục đầu tiên trong danh sách chọn
    static const int FIRST_OPTION = 1;

    // Mã phím đọc được từ _getch(): Enter, Backspace, ký tự in được đầu tiên
    static const int KEY_ENTER = 13;
    static const int KEY_BACKSPACE = 8;
    static const int KEY_FIRST_PRINTABLE = 32;

    // Mã đầu tiên của phím mở rộng (mũi tên, F1...), theo sau là một mã nữa
    static const int KEY_EXTENDED_ZERO = 0;
    static const int KEY_EXTENDED_E0 = 224;

    // Mã thứ hai của phím mũi tên lên và mũi tên xuống
    static const int KEY_UP = 72;
    static const int KEY_DOWN = 80;
};
