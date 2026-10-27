#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include "Util.h"

using namespace std;

template <typename T>
class AccountList {
private:
    static bool lessByUsername(const T& a, const T& b) {
        return false;
    }

    vector<T> m_items;
    string m_filePath;

public:
    AccountList(const string& filePath) {}

    // Bắt đầu đọc từng dòng của file tài khoản thành đối tượng tài khoản, trả về false nếu chưa có file
    bool load() {
        return false;
    }

    // Ghi lại các đối tượng tài khoản vào file (ghi đè cả file); trả về false nếu ghi lỗi
    bool save() const {
        return false;
    }

    // Trả về số lượng tài khoản của một loại Admin hay Employee
    int size() const {
        return 0;
    }

    // Trả về tham chiếu chiếu tới tài khoản ở vị trí index
    T& at(int index) {
        static T item;
        return item;
    }

    // Duyệt và trả về chỉ mục tài khoản đầu tiên của thuộc tính username khớp biến username; không có thì trả -1
    int indexOf(const string& username) const {
        return -1;
    }

    // Thêm một tài khoản item vào danh sách tài khoản
    void add(const T& item) {}

    // Xóa tài khoản ở vị trí index; chỉ đổi trong bộ nhớ, muốn lưu thì gọi phương thức save()
    void removeAt(int index) {}

    void sortByUsername() {}
};
