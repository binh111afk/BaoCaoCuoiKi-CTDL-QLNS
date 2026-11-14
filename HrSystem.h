#pragma once
#include <string>
#include <vector>
#include "Account.h"
#include "Admin.h"
#include "Employee.h"
#include "AccountList.h"
#include "UserProfile.h"

using namespace std;

// Bộ não của chương trình, nơi để giao diện console giao tiếp với các tầng bên dưới
class HrSystem {
private:
    // Trả về true nếu biến username đã có trong danh sách của nhân viên hoặc admin
    bool isUsernameTaken(const string& username) const;

    // Trả về đường dẫn file hồ sơ của nhân viên username (data/users/<username viết thường>.txt)
    static string profilePath(const string& username);

    // Ra lệnh cho lớp AccountList nạp các tệp txt thành các đối tượng tài khoản thật
    // Trả về true nếu quá trình thực hiện ổn
    bool loadFiles(vector<string>& messages);

    // Xóa bỏ các trường hợp tên đăng nhập của nhân viên bị trùng với admin và tên đăng nhập của nhân viên bị trùng với nhân viên (phòng hờ có người sửa thẳng tệp txt)
    // Trả về true nếu quá trình thực hiện ổn
    bool removeDuplicateEmployees(vector<string>& messages);

    // Tạo 3 tài khoản admin mặc định theo đề (trong trường hợp không đủ tài khoản mặc định)
    // Trả về true nếu quá trình thực hiện ổn
    bool createDefaultAdmins(vector<string>& messages);

    // Danh sách tài khoản admin, ghi trong file data/Administrators.txt
    AccountList<Admin> m_admins;

    // Danh sách tài khoản nhân viên, ghi trong file data/Employees.txt
    AccountList<Employee> m_employees;

public:
    // Tạo hệ thống với hai danh sách rỗng gắn với hai file txt, chưa đọc file (gọi initialize để nạp)
    HrSystem();

    // Phương thức này thực sự nạp dữ liệu của các tài khoản từ tệp txt vào
    // Biến messages ghi lại các log trong quá trình nạp (liệu có tài khoản nào trùng nhau hay không, ...)
    // Trả về true nếu quá trình thực hiện ổn
    bool initialize(vector<string>& messages);

    // Trả về true nếu như có tồn tại một tài khoản với username và password đúng
    // Đúng thi ghi vai trò vào Role; accountName là username được lưu trong file txt
    bool login(const string& username, const string& password,
               Role& role, string& accountName);

    // Tìm username trong danh sách nhân viên, trả về true nếu nhân viên đó cần phải thay đổi mật khẩu
    bool needsPasswordChange(const string& username);

    // Tìm một nhân viên có tên đăng nhập là username
    // Trả về true nếu password đúng với nhân viên đó
    bool verifyPassword(const string& username, const string& password);

    // Kiểm tra chuỗi username coi có đúng định dang hay không (giả sử cho nhân viên mới)
    // Trả về chuỗi rỗng nếu như username đó thỏa, trả về chuỗi mô tả lỗi nếu như không thỏa
    string checkNewUsername(const string& username);

    // Kiểm tra newPassword có dùng được làm mật khẩu mới của nhân viên username hay không
    // (đúng định dạng, không trùng mật khẩu mặc định, không trùng mật khẩu cũ)
    // Trả về chuỗi rỗng nếu thỏa, trả về chuỗi mô tả lỗi nếu không thỏa
    string checkNewPassword(const string& username, const string& newPassword);

    // Thêm nhân viên mới username với hồ sơ profile: ghi file hồ sơ rồi thêm vào Employees.txt (mật khẩu mặc định, bắt đổi ở lần đăng nhập đầu)
    // Trả về chuỗi rỗng nếu thành công, trả về chuỗi mô tả lỗi nếu ghi file không được
    string addEmployee(const string& username, const UserProfile& profile);

    // Xóa nhân viên username khỏi Employees.txt và xóa luôn file hồ sơ của nhân viên đó
    // Trả về chuỗi rỗng nếu thành công, trả về chuỗi mô tả lỗi nếu không có nhân viên đó hoặc ghi file không được
    string removeEmployee(const string& username);

    // Tìm nhân viên username rồi đọc hồ sơ của nhân viên đó vào profile
    // Trả về chuỗi rỗng nếu thành công, trả về chuỗi mô tả lỗi nếu không có nhân viên đó hoặc file hồ sơ bị thiếu hay hỏng
    string findEmployee(const string& username, UserProfile& profile);

    // Đổi thông tin field của nhân viên username thành value rồi ghi lại file hồ sơ
    // Trả về chuỗi rỗng nếu thành công, trả về chuỗi mô tả lỗi nếu value không hợp lệ, không có nhân viên đó hoặc ghi file không được
    string updateField(const string& username, ProfileField field, const string& value);

    // Ghi vào usernames tên đăng nhập của mọi nhân viên, sắp xếp tăng dần theo username
    void listEmployees(vector<string>& usernames);

    // Đổi mật khẩu của nhân viên username thành newPassword, tắt cờ bắt đổi mật khẩu rồi ghi lại Employees.txt
    // Trả về chuỗi rỗng nếu thành công, trả về chuỗi mô tả lỗi nếu không có nhân viên đó hoặc ghi file không được
    string changePassword(const string& username, const string& newPassword);
};
