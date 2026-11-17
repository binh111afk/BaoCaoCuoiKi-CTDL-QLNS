#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include "Util.h"

// Danh sách tài khoản (Admin hoặc Employee) nằm trong bộ nhớ, gắn với một file txt để nạp và ghi lại
template <typename T>
class AccountList {
public:
    // Giá trị indexOf trả về khi không tìm thấy tài khoản
    static const int NOT_FOUND = -1;

    /**********************************************************
    * @Description Tạo danh sách rỗng gắn với file filePath
    *
    * @attention Chưa đọc file, muốn nạp dữ liệu thì gọi load
    **********************************************************/
    AccountList(const std::string& filePath) : m_strFilePath(filePath) {
    }

    /**********************************************************
    * @Description Đọc từng dòng của file tài khoản thành đối tượng tài khoản
    *
    * @return true nếu đọc được file
    * @attention Trả về false nếu chưa có file
    * @attention Bỏ qua dòng rỗng, dòng sai định dạng và dòng trùng username với dòng trước
    **********************************************************/
    bool load() {
        this->m_items.clear();
        std::vector<std::string> lines;
        if (!Util::readLines(this->m_strFilePath, lines)) {
            return false;
        }

        for (const std::string& strLine : lines) {
            if (strLine.empty()) {
                continue;
            }

            T item;
            if (T::fromLine(strLine, item) && this->indexOf(item.getUsername()) == NOT_FOUND) {
                this->m_items.push_back(item);
            }
        }
        return true;
    }

    /**********************************************************
    * @Description Ghi lại các đối tượng tài khoản vào file (ghi đè cả file)
    *
    * @return true nếu ghi được file
    **********************************************************/
    bool save() const {
        std::vector<std::string> lines;
        for (const T& item : this->m_items) {
            lines.push_back(item.toLine());
        }
        return Util::writeLines(this->m_strFilePath, lines);
    }

    /**********************************************************
    * @Description Đếm số lượng tài khoản trong danh sách
    *
    * @return Số lượng tài khoản của một loại Admin hay Employee
    **********************************************************/
    int size() const {
        return static_cast<int>(this->m_items.size());
    }

    /**********************************************************
    * @Description Lấy tài khoản ở vị trí index
    *
    * @return Tham chiếu tới tài khoản ở vị trí index
    * @attention index phải nằm trong khoảng từ 0 đến size() - 1
    **********************************************************/
    T& at(const int index) {
        return this->m_items[static_cast<size_t>(index)];
    }

    /**********************************************************
    * @Description Duyệt danh sách để tìm tài khoản có username khớp (không phân biệt hoa thường)
    *
    * @return Chỉ mục của tài khoản đầu tiên khớp username
    * @attention Trả về NOT_FOUND nếu không có
    **********************************************************/
    int indexOf(const std::string& username) const {
        for (int iIndex = 0; iIndex < this->size(); iIndex++) {
            if (this->m_items[static_cast<size_t>(iIndex)].matchesUsername(username)) {
                return iIndex;
            }
        }
        return NOT_FOUND;
    }

    /**********************************************************
    * @Description Thêm một tài khoản item vào cuối danh sách
    *
    * @attention Chỉ đổi trong bộ nhớ, muốn lưu thì gọi save
    **********************************************************/
    void add(const T& item) {
        this->m_items.push_back(item);
    }

    /**********************************************************
    * @Description Xóa tài khoản ở vị trí index
    *
    * @attention Chỉ đổi trong bộ nhớ, muốn lưu thì gọi save
    * @attention index nằm ngoài danh sách thì không làm gì
    **********************************************************/
    void removeAt(const int index) {
        if (index >= 0 && index < this->size()) {
            this->m_items.erase(this->m_items.begin() + index);
        }
    }

    /**********************************************************
    * @Description Sắp xếp lại danh sách theo username tăng dần (so bằng chữ thường)
    **********************************************************/
    void sortByUsername() {
        std::sort(this->m_items.begin(), this->m_items.end(), AccountList::lessByUsername);
    }

private:
    /**********************************************************
    * @Description So sánh hai tài khoản theo username (chữ thường), dùng cho sortByUsername
    *
    * @return true nếu username của first đứng trước username của second
    **********************************************************/
    static bool lessByUsername(const T& first, const T& second) {
        return Util::toLower(first.getUsername()) < Util::toLower(second.getUsername());
    }

    // Các tài khoản đang có trong bộ nhớ
    std::vector<T> m_items;

    // Đường dẫn tới file txt chứa danh sách tài khoản
    std::string m_strFilePath;
};
