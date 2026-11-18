#pragma once

template <class DataType>
class LinkedList;

// Một phần tử (node) của danh sách liên kết đơn: chứa dữ liệu và con trỏ tới phần tử kế tiếp
template <class DataType>
class Node {
    // Lớp bạn để LinkedList sửa được con trỏ m_pNext
    friend class LinkedList<DataType>;

public:
    /**********************************************************
    * @Description Khởi tạo một Node mới có giá trị là data
    *
    * @attention Node mới chưa nối với phần tử nào (con trỏ kế tiếp là nullptr)
    **********************************************************/
    Node(const DataType& data);

    /**********************************************************
    * @Description Lấy dữ liệu đang chứa trong Node
    *
    * @return Tham chiếu tới dữ liệu, sửa qua tham chiếu này là sửa luôn dữ liệu trong Node
    **********************************************************/
    DataType& getData();

    /**********************************************************
    * @Description Lấy dữ liệu đang chứa trong Node (bản chỉ đọc)
    *
    * @return Tham chiếu hằng tới dữ liệu
    **********************************************************/
    const DataType& getData() const;

    /**********************************************************
    * @Description Lấy phần tử đứng ngay sau Node này
    *
    * @return Con trỏ tới phần tử kế tiếp, nullptr nếu Node này là phần tử cuối
    **********************************************************/
    Node<DataType>* getNext() const;

private:
    // Thành phần dữ liệu của Node
    DataType m_data;

    // Con trỏ trỏ đến Node kế tiếp
    Node<DataType>* m_pNext;
};

template <class DataType>
Node<DataType>::Node(const DataType& data)
    : m_data(data), m_pNext(nullptr) {
}

template <class DataType>
DataType& Node<DataType>::getData() {
    return this->m_data;
}

template <class DataType>
const DataType& Node<DataType>::getData() const {
    return this->m_data;
}

template <class DataType>
Node<DataType>* Node<DataType>::getNext() const {
    return this->m_pNext;
}
