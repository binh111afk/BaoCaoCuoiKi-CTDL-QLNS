#pragma once
#include <string>
#include "LinkedList.h"

// Các hàm tĩnh dùng chung: xử lý chuỗi, đọc ghi file và tạo thư mục
class Util {
public:
    /**********************************************************
    * @Description Bỏ khoảng trắng (dấu cách, tab, \r, \n) ở đầu và cuối chuỗi text
    *
    * @return Bản sao của text đã bỏ khoảng trắng đầu cuối
    * @attention Trả về chuỗi rỗng nếu text chỉ gồm khoảng trắng
    **********************************************************/
    static std::string trim(const std::string& text);

    /**********************************************************
    * @Description Đổi các chữ A-Z trong chuỗi text thành a-z
    *
    * @return Bản sao của text đã đổi thành chữ thường
    **********************************************************/
    static std::string toLower(const std::string& text);

    /**********************************************************
    * @Description So sánh hai chuỗi first và second mà không phân biệt hoa thường
    *
    * @return true nếu hai chuỗi giống nhau
    **********************************************************/
    static bool equalsIgnoreCase(const std::string& first, const std::string& second);

    /**********************************************************
    * @Description Kiểm tra chuỗi text có chỉ gồm các chữ số 0-9 hay không
    *
    * @return true nếu text không rỗng và chỉ gồm chữ số
    **********************************************************/
    static bool isAllDigits(const std::string& text);

    /**********************************************************
    * @Description Đọc từng dòng của file path (đã bỏ khoảng trắng đầu cuối) vào lines
    *
    * @return true nếu đọc được file
    * @attention Trả về false và lines rỗng nếu không mở được file
    **********************************************************/
    static bool readLines(const std::string& path, LinkedList<std::string>& lines);

    /**********************************************************
    * @Description Ghi đè file path bằng các dòng trong lines (chưa có file thì tạo mới)
    *
    * @return true nếu ghi được file
    * @attention Thư mục chứa file phải tồn tại trước
    **********************************************************/
    static bool writeLines(const std::string& path, const LinkedList<std::string>& lines);

    /**********************************************************
    * @Description Xóa file path khỏi ổ đĩa
    *
    * @return true nếu đã xóa
    * @attention Trả về false nếu file không có hoặc không xóa được
    **********************************************************/
    static bool deleteFile(const std::string& path);

    /**********************************************************
    * @Description Tạo thư mục path cùng các thư mục cha còn thiếu, nếu chưa có
    *
    * @return true nếu thư mục vừa mới tạo hoặc đã có sẵn
    * @attention path không có dấu / ở cuối
    **********************************************************/
    static bool ensureFolder(const std::string& path);

private:
    // Các ký tự được xem là khoảng trắng khi cắt chuỗi
    static const char* const WHITESPACE;
};
