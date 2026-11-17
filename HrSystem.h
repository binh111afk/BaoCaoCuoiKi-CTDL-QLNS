#pragma once
#include <string>
#include <vector>
#include "Account.h"
#include "Admin.h"
#include "Employee.h"
#include "AccountList.h"
#include "UserProfile.h"

// Bộ não của chương trình, nơi để giao diện console giao tiếp với các tầng bên dưới
class HrSystem {
public:
    /**********************************************************
    * @Description Tạo hệ thống với hai danh sách rỗng gắn với hai file txt
    *
    * @attention Chưa đọc file, muốn nạp dữ liệu thì gọi initialize
    **********************************************************/
    HrSystem();

    /**********************************************************
    * @Description Nạp dữ liệu của các tài khoản từ tệp txt vào, xử lý các trường hợp biên rồi tạo admin mặc định nếu thiếu
    *
    * @return true nếu quá trình thực hiện ổn
    * @attention Biến messages ghi lại các log trong quá trình nạp (liệu có tài khoản nào trùng nhau hay không, ...)
    **********************************************************/
    bool initialize(std::vector<std::string>& messages);

    /**********************************************************
    * @Description Kiểm tra có tồn tại một tài khoản với username và password đúng hay không
    *
    * @return true nếu như có tồn tại một tài khoản với username và password đúng
    * @attention Đúng thì ghi vai trò vào role; accountName là username được lưu trong file txt
    **********************************************************/
    bool login(const std::string& username, const std::string& password,
               Role& role, std::string& accountName);

    /**********************************************************
    * @Description Tìm username trong danh sách nhân viên rồi kiểm tra có cần đổi mật khẩu hay không
    *
    * @return true nếu nhân viên đó cần phải thay đổi mật khẩu
    **********************************************************/
    bool needsPasswordChange(const std::string& username);

    /**********************************************************
    * @Description Tìm một nhân viên có tên đăng nhập là username rồi kiểm tra mật khẩu
    *
    * @return true nếu password đúng với nhân viên đó
    **********************************************************/
    bool verifyPassword(const std::string& username, const std::string& password);

    /**********************************************************
    * @Description Kiểm tra chuỗi username coi có đúng định dang hay không (giả sử cho nhân viên mới)
    *
    * @return Chuỗi rỗng nếu như username đó thỏa, trả về chuỗi mô tả lỗi nếu như không thỏa
    * @attention Username đã có người dùng (admin hoặc nhân viên) cũng bị xem là không thỏa
    **********************************************************/
    std::string checkNewUsername(const std::string& username);

    /**********************************************************
    * @Description Kiểm tra newPassword có dùng được làm mật khẩu mới của nhân viên username hay không
    *
    * @return Chuỗi rỗng nếu thỏa, trả về chuỗi mô tả lỗi nếu không thỏa
    * @attention Mật khẩu phải đúng định dạng, không trùng mật khẩu mặc định và không trùng mật khẩu cũ
    **********************************************************/
    std::string checkNewPassword(const std::string& username, const std::string& newPassword);

    /**********************************************************
    * @Description Thêm nhân viên mới username với hồ sơ profile
    *
    * @return Chuỗi rỗng nếu thành công, trả về chuỗi mô tả lỗi nếu ghi file không được
    * @attention Ghi file hồ sơ rồi thêm vào Employees.txt với mật khẩu mặc định, bắt đổi ở lần đăng nhập đầu
    **********************************************************/
    std::string addEmployee(const std::string& username, const UserProfile& profile);

    /**********************************************************
    * @Description Xóa nhân viên username khỏi Employees.txt và xóa luôn file hồ sơ của nhân viên đó
    *
    * @return Chuỗi rỗng nếu thành công, trả về chuỗi mô tả lỗi nếu không có nhân viên đó hoặc ghi file không được
    **********************************************************/
    std::string removeEmployee(const std::string& username);

    /**********************************************************
    * @Description Tìm nhân viên username rồi đọc hồ sơ của nhân viên đó vào profile
    *
    * @return Chuỗi rỗng nếu thành công, trả về chuỗi mô tả lỗi nếu không có nhân viên đó hoặc file hồ sơ bị thiếu hay hỏng
    **********************************************************/
    std::string findEmployee(const std::string& username, UserProfile& profile);

    /**********************************************************
    * @Description Đổi thông tin field của nhân viên username thành value rồi ghi lại file hồ sơ
    *
    * @return Chuỗi rỗng nếu thành công, trả về chuỗi mô tả lỗi nếu value không hợp lệ, không có nhân viên đó hoặc ghi file không được
    **********************************************************/
    std::string updateField(const std::string& username, const ProfileField field,
                            const std::string& value);

    /**********************************************************
    * @Description Ghi vào usernames tên đăng nhập của mọi nhân viên
    *
    * @attention Danh sách được sắp xếp tăng dần theo username
    **********************************************************/
    void listEmployees(std::vector<std::string>& usernames);

    /**********************************************************
    * @Description Đổi mật khẩu của nhân viên username thành newPassword
    *
    * @return Chuỗi rỗng nếu thành công, trả về chuỗi mô tả lỗi nếu không có nhân viên đó hoặc ghi file không được
    * @attention Tắt cờ bắt đổi mật khẩu rồi ghi lại Employees.txt
    **********************************************************/
    std::string changePassword(const std::string& username, const std::string& newPassword);

private:
    /**********************************************************
    * @Description Kiểm tra username đã có trong danh sách của nhân viên hoặc admin hay chưa
    *
    * @return true nếu biến username đã có trong danh sách của nhân viên hoặc admin
    **********************************************************/
    bool isUsernameTaken(const std::string& username) const;

    /**********************************************************
    * @Description Tạo đường dẫn file hồ sơ của nhân viên username
    *
    * @return Đường dẫn có dạng data/users/<username viết thường>.txt
    **********************************************************/
    static std::string profilePath(const std::string& username);

    /**********************************************************
    * @Description Ra lệnh cho lớp AccountList nạp các tệp txt thành các đối tượng tài khoản thật
    *
    * @return true nếu quá trình thực hiện ổn
    * @attention Chưa có file thì tạo file rỗng, lỗi được ghi vào messages
    **********************************************************/
    bool loadFiles(std::vector<std::string>& messages);

    /**********************************************************
    * @Description Xóa bỏ các trường hợp tên đăng nhập của nhân viên bị trùng với admin và bị trùng với nhân viên khác
    *
    * @return true nếu quá trình thực hiện ổn
    * @attention Phòng hờ có người sửa thẳng tệp txt
    **********************************************************/
    bool removeDuplicateEmployees(std::vector<std::string>& messages);

    /**********************************************************
    * @Description Tạo 3 tài khoản admin mặc định theo đề (trong trường hợp không đủ tài khoản mặc định)
    *
    * @return true nếu quá trình thực hiện ổn
    **********************************************************/
    bool createDefaultAdmins(std::vector<std::string>& messages);

    // Số admin tối thiểu mà chương trình phải có, thiếu thì tạo admin mặc định
    static const int DEFAULT_ADMIN_COUNT = 3;

    // Phần đầu tên và mật khẩu của các admin mặc định (admin1, admin2, ...)
    static const std::string DEFAULT_ADMIN_PREFIX;
    static const std::string DEFAULT_ADMIN_PASSWORD;

    // Đường dẫn các file dữ liệu, thư mục hồ sơ và phần đuôi file hồ sơ
    static const std::string ADMIN_FILE_PATH;
    static const std::string EMPLOYEE_FILE_PATH;
    static const std::string PROFILE_FOLDER;
    static const std::string PROFILE_EXTENSION;

    // Các câu thông báo lỗi dùng lại nhiều lần
    static const std::string FILE_ERROR;
    static const std::string EMPLOYEE_NOT_FOUND;

    // Danh sách tài khoản admin, ghi trong file data/Administrators.txt
    AccountList<Admin> m_admins;

    // Danh sách tài khoản nhân viên, ghi trong file data/Employees.txt
    AccountList<Employee> m_employees;
};
