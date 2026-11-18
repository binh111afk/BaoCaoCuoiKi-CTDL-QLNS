#pragma once
#include <string>
#include "LinkedList.h"
#include "Util.h"

// Danh sách tài khoản (Admin hoặc Employee) nằm trong bộ nhớ, gắn với một file txt để nạp và ghi lại
// Các tài khoản được giữ trong một LinkedList<T> (danh sách liên kết đơn)
template <typename T>
class AccountList {
public:
    /**********************************************************
    * @Description Tạo danh sách rỗng gắn với file filePath
    *
    * @attention Chưa đọc file, muốn nạp dữ liệu thì gọi load
    **********************************************************/
    AccountList(const std::string& filePath);

    /**********************************************************
    * @Description Đọc từng dòng của file tài khoản thành đối tượng tài khoản
    *
    * @return true nếu đọc được file
    * @attention Trả về false nếu chưa có file
    * @attention Bỏ qua dòng rỗng, dòng sai định dạng và dòng trùng username với dòng trước
    **********************************************************/
    bool load();

    /**********************************************************
    * @Description Ghi lại các đối tượng tài khoản vào file (ghi đè cả file)
    *
    * @return true nếu ghi được file
    **********************************************************/
    bool save() const;

    /**********************************************************
    * @Description Đếm số lượng tài khoản trong danh sách
    *
    * @return Số lượng tài khoản của một loại Admin hay Employee
    **********************************************************/
    int getSize() const;

    /**********************************************************
    * @Description Lấy phần tử đầu của danh sách, dùng để duyệt các tài khoản bằng getNext
    *
    * @return Con trỏ tới phần tử đầu, nullptr nếu danh sách rỗng
    **********************************************************/
    Node<T>* getHead() const;

    /**********************************************************
    * @Description Duyệt danh sách để tìm tài khoản có username khớp (không phân biệt hoa thường)
    *
    * @return Con trỏ tới phần tử chứa tài khoản đầu tiên khớp username
    * @attention Trả về nullptr nếu không có
    **********************************************************/
    Node<T>* search(const std::string& username) const;

    /**********************************************************
    * @Description Thêm một tài khoản item vào cuối danh sách
    *
    * @attention Chỉ đổi trong bộ nhớ, muốn lưu thì gọi save
    **********************************************************/
    void add(const T& item);

    /**********************************************************
    * @Description Xóa phần tử node (lấy từ search hoặc getHead) khỏi danh sách
    *
    * @attention Chỉ đổi trong bộ nhớ, muốn lưu thì gọi save
    * @attention node là nullptr thì không làm gì; node phải thuộc danh sách này
    **********************************************************/
    void remove(Node<T>* node);

    /**********************************************************
    * @Description Sắp xếp lại danh sách theo username tăng dần (không phân biệt hoa thường)
    **********************************************************/
    void sortByUsername();

private:
    // Các tài khoản đang có trong bộ nhớ
    LinkedList<T> m_list;

    // Đường dẫn tới file txt chứa danh sách tài khoản
    std::string m_strFilePath;
};

template <typename T>
AccountList<T>::AccountList(const std::string& filePath)
    : m_strFilePath(filePath) {
}

template <typename T>
bool AccountList<T>::load() {
    this->m_list.clear();
    LinkedList<std::string> lines;
    if (!Util::readLines(this->m_strFilePath, lines)) {
        return false;
    }

    for (Node<std::string>* pLine = lines.getHead(); pLine != nullptr; pLine = pLine->getNext()) {
        if (pLine->getData().empty()) {
            continue;
        }

        T item;
        if (T::fromLine(pLine->getData(), item) && this->search(item.getUsername()) == nullptr) {
            this->m_list.addTail(item);
        }
    }
    return true;
}

template <typename T>
bool AccountList<T>::save() const {
    LinkedList<std::string> lines;
    for (Node<T>* pItem = this->m_list.getHead(); pItem != nullptr; pItem = pItem->getNext()) {
        lines.addTail(pItem->getData().toLine());
    }
    return Util::writeLines(this->m_strFilePath, lines);
}

template <typename T>
int AccountList<T>::getSize() const {
    return this->m_list.getSize();
}

template <typename T>
Node<T>* AccountList<T>::getHead() const {
    return this->m_list.getHead();
}

template <typename T>
Node<T>* AccountList<T>::search(const std::string& username) const {
    Node<T>* pItem = this->m_list.getHead();
    while (pItem != nullptr && !pItem->getData().matchesUsername(username)) {
        pItem = pItem->getNext();
    }
    return pItem;
}

template <typename T>
void AccountList<T>::add(const T& item) {
    this->m_list.addTail(item);
}

template <typename T>
void AccountList<T>::remove(Node<T>* node) {
    if (node == nullptr) {
        return;
    }
    this->m_list.removeAfter(this->m_list.searchPre(node));
}

template <typename T>
void AccountList<T>::sortByUsername() {
    this->m_list.selectionSort();
}
