#pragma once

#include <memory>
#include <stdexcept>

/**
 * @brief 简单实现一个单链表
 * 没有虚拟头节点
 * 维护了一个尾节点的指针
 * 提供基本的增删查改功能
 */
template <class T> class SingleLinkedList {
private:
  /**
   * @brief 单链表中的节点
   */
  struct Node {
    T value_;
    std::unique_ptr<Node> next_;
    explicit Node(T value) : value_(value), next_(nullptr) {}
  };

  std::unique_ptr<Node> head_; ///< 一直占有头节点
  Node *rear_ = nullptr; ///< 只作为观察指针，不实际拥有节点
  size_t size_ = 0;

public:
  /**
   * @brief 构造函数
   * 初始化成员变量
   */
  SingleLinkedList() : head_(nullptr), rear_(nullptr), size_(0) {}
  ~SingleLinkedList() = default; ///< 由于使用了智能指针，析构函数没有额外操作

  /**
   * @brief 头部添加
   * @note time: O(1)
   */
  void prepend(T value) {
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
  void append(T value) {
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
  void insert(size_t index, T value) {
    // 插入第一个
    if (index == 0) {
      prepend(value);
    }
    // 插入最后一个
    else if (index == size_) {
      append(value);
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
   * @throw popFront on empty list 从空链表中删除元素
   * @note time: O(1)
   */
  T popFront() {
    // 检查链表是否为空
    if (isEmpty()) {
      throw std::runtime_error("popFront on empty list");
    }
    std::unique_ptr<Node> node = std::move(head_);
    head_ = std::move(node->next_);
    T data = node->value_;
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
  T popBack() {
    // 检查链表是否为空
    if (isEmpty()) {
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
    T data = node->value_;
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
  T popAtIndex(size_t index) {
    if (index == 0) {
      return popFront();
    } else if (index == size_ - 1) {
      return popBack();
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
      T data = node->value_;
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
  T getFront() {
    if (isEmpty()) {
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
  T getBack() {
    if (isEmpty()) {
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
  T get(size_t index) {
    // 获取第一个节点的值
    if (index == 0) {
      return getFront();
    }
    // 获取最后一个节点的值
    else if (index == size_ - 1) {
      return getBack();
    }
    // 不是第一个也不是最后一个
    else if (index > 0 && index < size_ - 1) {
      Node *ptr = head_.get(); ///< 获取第一个节点的指针
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
  void set(size_t index, T value) {
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
  size_t size() const { return size_; }

  /**
   * @brief 判断链表是否为空
   * @return true 为空
   * @return false 不为空
   * @note time: O(1)
   */
  bool isEmpty() const { return size_ == 0; }
};