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

    AccountList<Admin> m_admins;
    AccountList<Employee> m_employees;

public:
    HrSystem();

    // Phương thức này thực sự nạp dữ liệu của các tài khoản từ tệp txt vào
    // Biến messages ghi lại các log trong quá trình nạp (liệu có tài khoản nào trùng nhau hay không, ...)
    // Trả về true nếu quá trình thực hiện ổn
    bool initialize(vector<string>& messages);

    bool login(const string& username, const string& password,
               Role& role, string& accountName);

    bool needsPasswordChange(const string& username);

    bool verifyPassword(const string& username, const string& password);

    string checkNewUsername(const string& username);

    string checkNewPassword(const string& username, const string& newPassword);

    string addEmployee(const string& username, const UserProfile& profile);

    string removeEmployee(const string& username);

    string findEmployee(const string& username, UserProfile& profile);

    string updateField(const string& username, ProfileField field, const string& value);

    void listEmployees(vector<string>& usernames);

    string changePassword(const string& username, const string& newPassword);
};
