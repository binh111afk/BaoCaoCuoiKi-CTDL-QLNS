#pragma once
#include <string>
#include "LinkedList.h"

// Bốn thông tin trong hồ sơ của một nhân viên, thứ tự cũng là thứ tự các dòng trong file [username].txt
enum class ProfileField { FULL_NAME, ADDRESS, PHONE, EMAIL };

// Hồ sơ của một nhân viên: họ tên, địa chỉ, số điện thoại, email
class UserProfile {
public:
    // Số lượng thông tin trong một hồ sơ
    static const int FIELD_COUNT = 4;

    /**********************************************************
    * @Description Lấy giá trị của thông tin field
    *
    * @return Giá trị của thông tin field
    **********************************************************/
    std::string get(const ProfileField field) const;

    /**********************************************************
    * @Description Gán value cho thông tin field
    **********************************************************/
    void set(const ProfileField field, const std::string& value);

    /**********************************************************
    * @Description Lấy tên hiển thị không dấu của thông tin field
    *
    * @return Tên hiển thị, ví dụ "Ho ten"
    **********************************************************/
    static std::string labelOf(const ProfileField field);

    /**********************************************************
    * @Description Đưa 4 thông tin của hồ sơ thành 4 dòng theo thứ tự trong ProfileField
    *
    * @return Danh sách liên kết gồm 4 chuỗi
    **********************************************************/
    LinkedList<std::string> toLines() const;

    /**********************************************************
    * @Description Lấy 4 dòng đầu của lines gán vào hồ sơ out
    *
    * @return true nếu lines có từ 4 dòng trở lên
    * @attention Trả về false thì out không bị đổi
    **********************************************************/
    static bool fromLines(const LinkedList<std::string>& lines, UserProfile& out);

private:
    // Giá trị của 4 thông tin, đánh số theo ProfileField
    std::string m_strValues[FIELD_COUNT];
};
