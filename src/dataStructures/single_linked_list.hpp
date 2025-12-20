#pragma once

#include <memory>
#include <stdexcept>

/**
 * @brief 简单实现一个单链表
 * 没有虚拟头节点
 * 维护了一个尾节点的指针
 * 提供基本的增删查改功能
 */
template <class T>
class SingleLinkedList {
   public:
    using value_type = T;
    using size_type = std::size_t;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;

   private:
    /**
     * @brief 单链表中的节点
     */
    struct Node {
        value_type value_;
        std::unique_ptr<Node> next_;
        Node() = default;
        explicit Node(const_reference value) : value_(value), next_(nullptr) {
        }
        explicit Node(T &&value) noexcept : value_(std::move(value)), next_(nullptr) {
        }
    };

    std::unique_ptr<Node> head_;  ///< 一直占有头节点
    Node *rear_ = nullptr;        ///< 只作为观察指针，不实际拥有节点
    size_type size_ = 0;

   public:
    /**
     * @brief 构造函数
     * 初始化成员变量
     */
    SingleLinkedList() : head_(nullptr), rear_(nullptr), size_(0) {
    }
    ~SingleLinkedList() = default;  ///< 由于使用了智能指针，析构函数没有额外操作

    /**
     * @brief 头部添加
     * @note time: O(1)
     */
    void push_front(value_type value) {
        std::unique_ptr<Node> node = std::make_unique<Node>(value);
        node->next_ = std::move(head_);
        head_ = std::move(node);
        // 如果添加的是唯一一个元素，rear也要指向它
        if (size_ == 0) {
            rear_ = head_.get();
        }
        size_++;
    }

    /**
     * @brief 尾部添加
     * @note time: O(1)
     */
    void push_back(value_type value) {
        std::unique_ptr<Node> node = std::make_unique<Node>(value);
        if (size_ == 0) {
            head_ = std::move(node);
            rear_ = head_.get();
        } else {
            rear_->next_ = std::move(node);
            rear_ = rear_->next_.get();
        }
        size_++;
    }

    /**
     * @brief 指定索引位置添加
     * @throw insert out of range 越界添加
     * @note time: O(n)
     */
    void insert(size_type index, value_type value) {
        // 插入第一个
        if (index == 0) {
            push_front(value);
        }
        // 插入最后一个
        else if (index == size_) {
            push_back(value);
        }
        // 不是第一个也不是最后一个
        else if (index > 0 && index < size_) {
            // 定义一个指针，指向要插入位置的前一个节点
            Node *ptr = head_.get();
            for (int i = 0; i < index - 1; ++i) {
                ptr = ptr->next_.get();
            }
            auto node = std::make_unique<Node>(value);
            node->next_ = std::move(ptr->next_);
            ptr->next_ = std::move(node);
            size_++;
        } else {
            throw std::out_of_range("insert out of range");
        }
    }

    /**
     * @brief 头部删除
     * @throw pop_front on empty list 从空链表中删除元素
     * @note time: O(1)
     */
    value_type pop_front() {
        // 检查链表是否为空
        if (is_empty()) {
            throw std::runtime_error("pop_front on empty list");
        }
        std::unique_ptr<Node> node = std::move(head_);
        head_ = std::move(node->next_);
        value_type data = node->value_;
        size_--;
        // 如果删除后没有元素了，rear指向nullptr
        if (size_ == 0) {
            rear_ = nullptr;
        }
        return data;
    }

    /**
     * @brief 尾部删除
     * @throw popBack on empty list 从空链表中删除元素
     * @note O(n)
     */
    value_type pop_back() {
        // 检查链表是否为空
        if (is_empty()) {
            throw std::runtime_error("popBack on empty list");
        }
        // 定义一个指针，指向最后一个节点的前一个节点
        Node *ptr = head_.get();
        while (ptr->next_.get() != rear_) {
            ptr = ptr->next_.get();
        }
        std::unique_ptr<Node> node = std::move(ptr->next_);
        ptr->next_ = nullptr;
        // rear指向最后一个节点
        rear_ = ptr;
        value_type data = node->value_;
        size_--;
        // 如果删除后链表为空
        if (size_ == 0) {
            head_ = nullptr;
            rear_ = nullptr;
        }
        return data;
    }

    /**
     * @brief 指定索引位置删除
     * 删除第一个会调用popFront
     * 删除最后一个会调用popBack
     * @throw pop out of range 越界删除
     * @note time: O(n)
     */
    value_type pop_at_index(size_type index) {
        if (index == 0) {
            return pop_front();
        } else if (index == size_ - 1) {
            return pop_back();
        } else if (index > 0 && index < size_ - 1) {
            // 不是第一个也不是最后一个
            // 获得要删除节点的前一个节点
            Node *ptr = head_.get();
            for (int i = 0; i < index - 1; ++i) {
                ptr = ptr->next_.get();
            }
            // 创建unique_ptr转移所有权
            std::unique_ptr<Node> node = std::move(ptr->next_);
            ptr->next_ = std::move(node->next_);
            value_type data = node->value_;
            size_--;
            return data;
        } else {
            throw std::out_of_range("pop out of range");
        }
    }

    /**
     * @brief 获取链表的第一个节点的值
     * @return 链表的第一个节点的值
     * @throw getFront for empyt list 从空链表中获取节点
     * @note time: O(1)
     */
    value_type get_front() {
        if (is_empty()) {
            throw std::runtime_error("getFront for empyt list");
        }
        return head_->value_;
    }

    /**
     * @brief 获取链表的最后一个节点的值
     * @return 链表的最后一个节点的值
     * @throw getBack for empty list 从空链表中获取节点
     * @note time: O(1)
     */
    value_type get_back() {
        if (is_empty()) {
            throw std::runtime_error("getBack for empty list");
        }
        return rear_->value_;
    }

    /**
     * @brief 获取指定索引位置节点的值
     * @param index 要指定的节点
     * @return 指定索引位置节点的值
     * @throw get out of range 越界获取
     * @note time: O(n)
     */
    value_type get(size_type index) {
        // 获取第一个节点的值
        if (index == 0) {
            return get_front();
        }
        // 获取最后一个节点的值
        else if (index == size_ - 1) {
            return get_back();
        }
        // 不是第一个也不是最后一个
        else if (index > 0 && index < size_ - 1) {
            Node *ptr = head_.get();  ///< 获取第一个节点的指针
            for (int i = 0; i < index; ++i) {
                ptr = ptr->next_.get();
            }
            return ptr->value_;
        } else {
            throw std::out_of_range("get out of range");
        }
    }

    /**
     * @brief 修改指定索引位置的节点的值
     * @param index 要指定的索引
     * @param value 新的值
     * @throw set out of range 越界修改
     * @note time: O(n)
     */
    void set(size_type index, value_type value) {
        if (index >= size_) {
            throw std::out_of_range("set out of range");
        }
        // 修改最后一个节点的值
        else if (index == size_ - 1) {
            rear_->value_ = value;
        }
        // 修改不是最后一个节点的值
        else {
            Node *ptr = head_.get();
            for (int i = 0; i < index; ++i) {
                ptr = ptr->next_.get();
            }
            ptr->value_ = value;
        }
    }

    /**
     * @brief 返回链表节点数
     * @return 链表节点数
     * @note time: O(1)
     */
    size_type size() const {
        return size_;
    }

    /**
     * @brief 判断链表是否为空
     * @return true 为空
     * @return false 不为空
     * @note time: O(1)
     */
    bool is_empty() const {
        return size_ == 0;
    }
};