#pragma once
#include <utility>
#include "Node.h"

// Danh sách liên kết đơn có con trỏ m_pHead (phần tử đầu), m_pTail (phần tử cuối) và m_iSize (số phần tử)
// DataType phải so sánh được bằng == (cho search, remove) và < (cho selectionSort)
template <class DataType>
class LinkedList {
public:
    /**********************************************************
    * @Description Tạo danh sách rỗng
    **********************************************************/
    LinkedList();

    /**********************************************************
    * @Description Tạo danh sách mới bằng cách sao chép từng phần tử của other
    *
    * @attention Sao chép sâu, hai danh sách không dùng chung Node nào
    **********************************************************/
    LinkedList(const LinkedList<DataType>& other);

    /**********************************************************
    * @Description Hủy danh sách, giải phóng bộ nhớ của mọi Node
    **********************************************************/
    ~LinkedList();

    /**********************************************************
    * @Description Gán danh sách other cho danh sách này
    *
    * @return Chính danh sách này
    * @attention Xóa hết phần tử cũ rồi sao chép sâu từ other
    **********************************************************/
    LinkedList<DataType>& operator=(const LinkedList<DataType>& other);

    /**********************************************************
    * @Description Thêm một phần tử có giá trị data vào đầu LinkedList
    **********************************************************/
    void addHead(const DataType& data);

    /**********************************************************
    * @Description Thêm một phần tử có giá trị data vào cuối LinkedList
    **********************************************************/
    void addTail(const DataType& data);

    /**********************************************************
    * @Description Thêm một phần tử có giá trị data vào sau phần tử node trong LinkedList
    *
    * @attention node là nullptr thì thêm vào đầu danh sách
    * @attention node phải là phần tử của chính danh sách này
    **********************************************************/
    void addAfter(Node<DataType>* node, const DataType& data);

    /**********************************************************
    * @Description Tìm một phần tử trong LinkedList khi biết khóa data
    *
    * @return Con trỏ tới phần tử đầu tiên bằng data, nullptr nếu không tìm thấy
    **********************************************************/
    Node<DataType>* search(const DataType& data) const;

    /**********************************************************
    * @Description Tìm phần tử đứng ngay trước phần tử node trong LinkedList
    *
    * @return Con trỏ tới phần tử đứng trước node, nullptr nếu node là phần tử đầu hoặc không tìm thấy
    **********************************************************/
    Node<DataType>* searchPre(const Node<DataType>* node) const;

    /**********************************************************
    * @Description Xóa phần tử ở đầu LinkedList
    *
    * @attention Danh sách rỗng thì không làm gì
    **********************************************************/
    void removeHead();

    /**********************************************************
    * @Description Xóa phần tử ở cuối LinkedList
    *
    * @attention Danh sách rỗng thì không làm gì
    **********************************************************/
    void removeTail();

    /**********************************************************
    * @Description Xóa phần tử đứng ngay sau phần tử node trong LinkedList
    *
    * @attention node là nullptr thì xóa phần tử đầu danh sách
    * @attention node là phần tử cuối thì không làm gì
    **********************************************************/
    void removeAfter(Node<DataType>* node);

    /**********************************************************
    * @Description Xóa phần tử đầu tiên có khóa là data trong LinkedList
    *
    * @attention Không có phần tử nào bằng data thì không làm gì
    **********************************************************/
    void remove(const DataType& data);

    /**********************************************************
    * @Description Xóa toàn bộ LinkedList
    **********************************************************/
    void clear();

    /**********************************************************
    * @Description Sắp xếp danh sách tăng dần theo thuật toán Selection Sort
    *
    * @attention Đổi chỗ dữ liệu giữa các Node chứ không đổi chỗ Node, nên mọi con trỏ Node đang giữ vẫn hợp lệ
    **********************************************************/
    void selectionSort();

    /**********************************************************
    * @Description Lấy số lượng phần tử có trong LinkedList
    *
    * @return Số phần tử có trong LinkedList
    **********************************************************/
    int getSize() const;

    /**********************************************************
    * @Description Kiểm tra LinkedList có rỗng hay không
    *
    * @return true nếu danh sách không có phần tử nào
    **********************************************************/
    bool isEmpty() const;

    /**********************************************************
    * @Description Lấy phần tử đầu của LinkedList, dùng để duyệt danh sách bằng getNext
    *
    * @return Con trỏ tới phần tử đầu, nullptr nếu danh sách rỗng
    **********************************************************/
    Node<DataType>* getHead() const;

private:
    /**********************************************************
    * @Description Tìm phần tử nhỏ nhất (theo <) từ phần tử start đến hết danh sách
    *
    * @return Con trỏ tới phần tử nhỏ nhất, là start nếu không có phần tử nào nhỏ hơn
    * @attention start không được là nullptr
    **********************************************************/
    Node<DataType>* findMin(Node<DataType>* start) const;

    /**********************************************************
    * @Description Thêm lần lượt từng phần tử của other vào cuối danh sách này
    **********************************************************/
    void copyFrom(const LinkedList<DataType>& other);

    // Con trỏ trỏ tới phần tử đầu danh sách
    Node<DataType>* m_pHead;

    // Con trỏ trỏ tới phần tử cuối danh sách
    Node<DataType>* m_pTail;

    // Số phần tử hiện có của danh sách
    int m_iSize;
};

template <class DataType>
LinkedList<DataType>::LinkedList()
    : m_pHead(nullptr), m_pTail(nullptr), m_iSize(0) {
}

template <class DataType>
LinkedList<DataType>::LinkedList(const LinkedList<DataType>& other)
    : m_pHead(nullptr), m_pTail(nullptr), m_iSize(0) {
    this->copyFrom(other);
}

template <class DataType>
LinkedList<DataType>::~LinkedList() {
    this->clear();
}

template <class DataType>
LinkedList<DataType>& LinkedList<DataType>::operator=(const LinkedList<DataType>& other) {
    if (this != &other) {
        this->clear();
        this->copyFrom(other);
    }
    return *this;
}

template <class DataType>
void LinkedList<DataType>::addHead(const DataType& data) {
    Node<DataType>* const pAdd = new Node<DataType>(data);
    if (this->m_pHead == nullptr) {
        this->m_pHead = pAdd;
        this->m_pTail = pAdd;
    } else {
        pAdd->m_pNext = this->m_pHead;
        this->m_pHead = pAdd;
    }
    this->m_iSize++;
}

template <class DataType>
void LinkedList<DataType>::addTail(const DataType& data) {
    Node<DataType>* const pAdd = new Node<DataType>(data);
    if (this->m_pHead == nullptr) {
        this->m_pHead = pAdd;
        this->m_pTail = pAdd;
    } else {
        this->m_pTail->m_pNext = pAdd;
        this->m_pTail = pAdd;
    }
    this->m_iSize++;
}

template <class DataType>
void LinkedList<DataType>::addAfter(Node<DataType>* node, const DataType& data) {
    if (node == nullptr) {
        this->addHead(data);
        return;
    }

    Node<DataType>* const pAdd = new Node<DataType>(data);
    pAdd->m_pNext = node->m_pNext;
    node->m_pNext = pAdd;
    if (node == this->m_pTail) {
        this->m_pTail = pAdd;
    }
    this->m_iSize++;
}

template <class DataType>
Node<DataType>* LinkedList<DataType>::search(const DataType& data) const {
    Node<DataType>* pWalker = this->m_pHead;
    while (pWalker != nullptr && !(pWalker->m_data == data)) {
        pWalker = pWalker->m_pNext;
    }
    return pWalker;
}

template <class DataType>
Node<DataType>* LinkedList<DataType>::searchPre(const Node<DataType>* node) const {
    Node<DataType>* pWalker = this->m_pHead;
    if (pWalker == node) {
        return nullptr;
    }

    while (pWalker != nullptr && pWalker->m_pNext != node) {
        pWalker = pWalker->m_pNext;
    }
    return pWalker;
}

template <class DataType>
void LinkedList<DataType>::removeHead() {
    if (this->m_pHead == nullptr) {
        return;
    }

    Node<DataType>* const pTemp = this->m_pHead;
    this->m_pHead = this->m_pHead->m_pNext;
    delete pTemp;
    if (this->m_pHead == nullptr) {
        this->m_pTail = nullptr;
    }
    this->m_iSize--;
}

template <class DataType>
void LinkedList<DataType>::removeTail() {
    if (this->m_pHead == nullptr) {
        return;
    }

    Node<DataType>* const pTemp = this->m_pTail;
    this->m_pTail = this->searchPre(this->m_pTail);
    delete pTemp;
    if (this->m_pTail != nullptr) {
        this->m_pTail->m_pNext = nullptr;
    } else {
        this->m_pHead = nullptr;
    }
    this->m_iSize--;
}

template <class DataType>
void LinkedList<DataType>::removeAfter(Node<DataType>* node) {
    if (node == nullptr) {
        this->removeHead();
        return;
    }

    Node<DataType>* const pTemp = node->m_pNext;
    if (pTemp == nullptr) {
        return;
    }

    if (pTemp == this->m_pTail) {
        this->m_pTail = node;
    }
    node->m_pNext = pTemp->m_pNext;
    delete pTemp;
    this->m_iSize--;
}

template <class DataType>
void LinkedList<DataType>::remove(const DataType& data) {
    Node<DataType>* pWalker = this->m_pHead;
    Node<DataType>* pPre = nullptr;
    while (pWalker != nullptr && !(pWalker->m_data == data)) {
        pPre = pWalker;
        pWalker = pWalker->m_pNext;
    }

    if (pWalker == nullptr) {
        return;
    }
    this->removeAfter(pPre);
}

template <class DataType>
void LinkedList<DataType>::clear() {
    while (this->m_pHead != nullptr) {
        this->removeHead();
    }
}

template <class DataType>
void LinkedList<DataType>::selectionSort() {
    Node<DataType>* pWalker = this->m_pHead;
    while (pWalker != nullptr && pWalker->m_pNext != nullptr) {
        Node<DataType>* const pMin = this->findMin(pWalker);
        std::swap(pMin->m_data, pWalker->m_data);
        pWalker = pWalker->m_pNext;
    }
}

template <class DataType>
int LinkedList<DataType>::getSize() const {
    return this->m_iSize;
}

template <class DataType>
bool LinkedList<DataType>::isEmpty() const {
    return this->m_iSize == 0;
}

template <class DataType>
Node<DataType>* LinkedList<DataType>::getHead() const {
    return this->m_pHead;
}

template <class DataType>
Node<DataType>* LinkedList<DataType>::findMin(Node<DataType>* start) const {
    Node<DataType>* pMin = start;
    Node<DataType>* pWalker = start->m_pNext;
    while (pWalker != nullptr) {
        if (pWalker->m_data < pMin->m_data) {
            pMin = pWalker;
        }
        pWalker = pWalker->m_pNext;
    }
    return pMin;
}

template <class DataType>
void LinkedList<DataType>::copyFrom(const LinkedList<DataType>& other) {
    Node<DataType>* pWalker = other.m_pHead;
    while (pWalker != nullptr) {
        this->addTail(pWalker->m_data);
        pWalker = pWalker->m_pNext;
    }
}
