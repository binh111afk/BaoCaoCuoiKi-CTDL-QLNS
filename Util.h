#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Các hàm tĩnh dùng chung: xử lý chuỗi, đọc ghi file và tạo thư mục
class Util {
public:
    // Trả về bản sao của chuỗi s đã bỏ khoảng trắng (dấu cách, tab, \r, \n) ở đầu và cuối
    static string trim(const string& s) {
        size_t first = s.find_first_not_of(" \t\r\n");
        if (first == string::npos) {
            return "";
        }
        size_t last = s.find_last_not_of(" \t\r\n");
        return s.substr(first, last - first + 1);
    }

    // Trả về bản sao của chuỗi s với các chữ A-Z đổi thành a-z
    static string toLower(const string& s) {
        string result = s;
        for (size_t i = 0; i < result.size(); i++) {
            if (result[i] >= 'A' && result[i] <= 'Z') {
                result[i] = static_cast<char>(result[i] - 'A' + 'a');
            }
        }
        return result;
    }

    // Trả về true nếu hai chuỗi a và b giống nhau khi không phân biệt hoa thường
    static bool equalsIgnoreCase(const string& a, const string& b) {
        return toLower(a) == toLower(b);
    }

    // Trả về true nếu chuỗi s không rỗng và chỉ gồm các chữ số 0-9
    static bool isAllDigits(const string& s) {
        if (s.empty()) {
            return false;
        }
        for (size_t i = 0; i < s.size(); i++) {
            if (s[i] < '0' || s[i] > '9') {
                return false;
            }
        }
        return true;
    }

    // Đọc từng dòng của file path (đã bỏ khoảng trắng đầu cuối) vào lines, trả về false nếu không mở được file
    static bool readLines(const string& path, vector<string>& lines) {
        lines.clear();
        ifstream file(path);
        if (!file.is_open()) {
            return false;
        }

        string line;
        while (getline(file, line)) {
            lines.push_back(trim(line));
        }
        return true;
    }

    // Ghi đè file path bằng các dòng trong lines (chưa có file thì tạo mới), trả về false nếu không ghi được
    static bool writeLines(const string& path, const vector<string>& lines) {
        ofstream file(path);
        if (!file.is_open()) {
            return false;
        }

        for (size_t i = 0; i < lines.size(); i++) {
            file << lines[i] << "\n";
        }
        file.flush();
        return !file.fail();
    }

    // Xóa file path, trả về true nếu đã xóa, false nếu file không có hoặc không xóa được
    static bool deleteFile(const string& path) {
        error_code error;
        return filesystem::remove(path, error);
    }

    // Tạo thư mục path cùng các thư mục cha còn thiếu, nếu chưa có; trả true nếu thư mục vừa mới tạo hoặc đã có sẵn
    static bool ensureFolder(const string& path) {
        error_code error;
        filesystem::create_directories(path, error);
        return filesystem::is_directory(path, error);
    }
};
