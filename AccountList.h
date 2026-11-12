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
        return Util::toLower(a.getUsername()) < Util::toLower(b.getUsername());
    }

    vector<T> m_items;
    string m_filePath;

public:
    AccountList(const string& filePath) : m_filePath(filePath) {}

    // Bắt đầu đọc từng dòng của file tài khoản thành đối tượng tài khoản, trả về false nếu chưa có file
    bool load() {
        m_items.clear();
        vector<string> lines;
        if (!Util::readLines(m_filePath, lines)) {
            return false;
        }

        for (const string& line : lines) {
            if (line.empty()) {
                continue;
            }
            T item;
            if (T::fromLine(line, item)) {
                if (indexOf(item.getUsername()) == -1) {
                    m_items.push_back(item);
                }
            }
        }
        return true;
    }

    // Ghi lại các đối tượng tài khoản vào file (ghi đè cả file); trả về false nếu ghi lỗi
    bool save() const {
        vector<string> lines;
        for (const T& item : m_items) {
            lines.push_back(item.toLine());
        }
        return Util::writeLines(m_filePath, lines);
    }

    // Trả về số lượng tài khoản của một loại Admin hay Employee
    int size() const {
        return static_cast<int>(m_items.size());
    }

    // Trả về tham chiếu tới tài khoản ở vị trí index
    T& at(int index) {
        return m_items[index];
    }

    // Duyệt và trả về chỉ mục tài khoản đầu tiên có thuộc tính username khớp biến username; không có thì trả -1
    int indexOf(const string& username) const {
        for (int i = 0; i < size(); ++i) {
            if (m_items[i].matchesUsername(username)) {
                return i;
            }
        }
        return -1;
    }

    // Thêm một tài khoản item vào danh sách tài khoản
    void add(const T& item) {
        m_items.push_back(item);
    }

    // Xóa tài khoản ở vị trí index; chỉ đổi trong bộ nhớ, muốn lưu thì gọi phương thức save()
    void removeAt(int index) {
        if (index >= 0 && index < size()) {
            m_items.erase(m_items.begin() + index);
        }
    }

    // Sắp xếp lại danh sách theo username tăng dần (so bằng chữ thường)
    void sortByUsername() {
        sort(m_items.begin(), m_items.end(), lessByUsername);
    }
};