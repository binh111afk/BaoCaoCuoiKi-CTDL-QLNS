#pragma once
#include <cstddef>
#include <string>
#include "UserProfile.h"

// Kiểm tra định dạng dữ liệu nhập, mỗi hàm trả về chuỗi rỗng nếu hợp lệ, không thì trả về câu mô tả lỗi
class Validator {
public:
    /**********************************************************
    * @Description Kiểm tra username có dùng được làm tên đăng nhập không
    *
    * @return Chuỗi rỗng nếu hợp lệ, không thì trả về câu mô tả lỗi
    * @attention Username dài 3-20 ký tự, chỉ gồm chữ không dấu, số và _, bắt đầu bằng chữ
    * @attention Không được trùng tên file danh riêng của Windows (con, prn, aux, nul, com1-9, lpt1-9)
    **********************************************************/
    static std::string checkUsername(const std::string& username);

    /**********************************************************
    * @Description Kiểm tra password có dùng được làm mật khẩu không
    *
    * @return Chuỗi rỗng nếu hợp lệ, không thì trả về câu mô tả lỗi
    * @attention Mật khẩu dài 6-20 ký tự, mỗi ký tự có mã từ 33 đến 126 (không dấu cách, không chữ có dấu)
    **********************************************************/
    static std::string checkPassword(const std::string& password);

    /**********************************************************
    * @Description Kiểm tra fullName có dùng được làm họ tên không
    *
    * @return Chuỗi rỗng nếu hợp lệ, không thì trả về câu mô tả lỗi
    * @attention Họ tên dài 1-50 ký tự, chỉ gồm chữ cái không dấu và dấu cách
    **********************************************************/
    static std::string checkFullName(const std::string& fullName);

    /**********************************************************
    * @Description Kiểm tra address có dùng được làm địa chỉ không
    *
    * @return Chuỗi rỗng nếu hợp lệ, không thì trả về câu mô tả lỗi
    * @attention Địa chỉ dài 1-100 ký tự, mỗi ký tự có mã từ 32 đến 126
    **********************************************************/
    static std::string checkAddress(const std::string& address);

    /**********************************************************
    * @Description Kiểm tra phone có dùng được làm số điện thoại không
    *
    * @return Chuỗi rỗng nếu hợp lệ, không thì trả về câu mô tả lỗi
    * @attention Số điện thoại gồm đúng 10 chữ số và bắt đầu bằng 0
    **********************************************************/
    static std::string checkPhone(const std::string& phone);

    /**********************************************************
    * @Description Kiểm tra email có dùng được làm email không
    *
    * @return Chuỗi rỗng nếu hợp lệ, không thì trả về câu mô tả lỗi
    * @attention Email có dạng ten@ten-mien.duoi, tối đa 50 ký tự, không có dấu cách
    **********************************************************/
    static std::string checkEmail(const std::string& email);

    /**********************************************************
    * @Description Kiểm tra value có hợp lệ cho thông tin field không, bằng cách gọi hàm kiểm tương ứng
    *
    * @return Chuỗi rỗng nếu hợp lệ, không thì trả về câu mô tả lỗi
    **********************************************************/
    static std::string checkField(const ProfileField field, const std::string& value);

private:
    /**********************************************************
    * @Description Kiểm tra mọi ký tự của text có mã nằm trong khoảng từ minCode đến maxCode không
    *
    * @return true nếu mọi ký tự đều nằm trong khoảng
    **********************************************************/
    static bool isAllCharsInRange(const std::string& text, const int minCode, const int maxCode);

    /**********************************************************
    * @Description Kiểm tra mọi ký tự của text có là chữ không dấu, số hoặc dấu _ không
    *
    * @return true nếu mọi ký tự đều hợp lệ
    **********************************************************/
    static bool isAllUsernameChars(const std::string& text);

    /**********************************************************
    * @Description Kiểm tra mọi ký tự của text có là chữ không dấu hoặc dấu cách không
    *
    * @return true nếu mọi ký tự đều hợp lệ
    **********************************************************/
    static bool isAllLettersOrSpaces(const std::string& text);

    /**********************************************************
    * @Description Kiểm tra lowerName có trùng tên file danh riêng của Windows không
    *
    * @return true nếu trùng
    * @attention lowerName phải là chữ thường
    **********************************************************/
    static bool isReservedName(const std::string& lowerName);

    // Độ dài ngắn nhất và dài nhất của username
    static const std::size_t MIN_USERNAME_LENGTH = 3;
    static const std::size_t MAX_USERNAME_LENGTH = 20;

    // Độ dài ngắn nhất và dài nhất của mật khẩu
    static const std::size_t MIN_PASSWORD_LENGTH = 6;
    static const std::size_t MAX_PASSWORD_LENGTH = 20;

    // Độ dài dài nhất của họ tên, địa chỉ, email
    static const std::size_t MAX_FULL_NAME_LENGTH = 50;
    static const std::size_t MAX_ADDRESS_LENGTH = 100;
    static const std::size_t MAX_EMAIL_LENGTH = 50;

    // Số điện thoại gồm đúng ngần này chữ số, chữ số đầu là PHONE_FIRST_DIGIT
    static const std::size_t PHONE_LENGTH = 10;
    static const char PHONE_FIRST_DIGIT = '0';

    // Mã ASCII của dấu cách, của ký tự nhìn thấy đầu tiên (sau dấu cách) và cuối cùng
    static const int ASCII_SPACE = 32;
    static const int ASCII_FIRST_VISIBLE = 33;
    static const int ASCII_LAST_VISIBLE = 126;

    // Số lớn nhất đứng sau tên com và lpt của Windows (com1 đến com9, lpt1 đến lpt9)
    static const int MAX_DEVICE_NUMBER = 9;

    // Các tên file dành riêng của Windows (không có số đi kèm), lưu trong mảng RESERVED_NAME_COUNT phần tử
    static const std::size_t RESERVED_NAME_COUNT = 4;
    static const char* const RESERVED_NAMES[RESERVED_NAME_COUNT];

    // Các câu thông báo lỗi
    static const std::string ERROR_USERNAME;
    static const std::string ERROR_USERNAME_RESERVED;
    static const std::string ERROR_PASSWORD;
    static const std::string ERROR_FULL_NAME;
    static const std::string ERROR_ADDRESS;
    static const std::string ERROR_PHONE;
    static const std::string ERROR_EMAIL;
};
