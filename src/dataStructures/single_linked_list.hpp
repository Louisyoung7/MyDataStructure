#pragma once

#include <memory>
#include <stdexcept>
using std::make_unique;
using std::out_of_range;
using std::runtime_error;
using std::unique_ptr;

/*
 * @brief 简单实现一个单链表
 */
class SingleLinkedList {
private:
  /*
   * @brief 单链表中的节点
   */
  struct Node {
    int value_;
    unique_ptr<Node> next_; //? 为什么使用unique_ptr?
    explicit Node(int value) : value_(value), next_(nullptr) {}
  };

  unique_ptr<Node> head_; ///< 一直占有头节点
  Node *rear_ = nullptr;  //? 为什么这里的rear_又不用unique_ptr了?
  size_t size_ = 0;

public:
  /*
   * @brief 构造函数
   * 初始化成员变量
   */
  SingleLinkedList() : head_(nullptr), rear_(nullptr), size_(0) {}
  ~SingleLinkedList() {
    // TODO
  }

  /*
   * @brief 头部添加
   * @note time: O(1)
   */
  void prepend(int value) {
    unique_ptr<Node> node = make_unique<Node>(value);
    node->next_ = std::move(head_); //? 为什么这里要用std::move?
    head_ = std::move(node);
    // 如果添加的是唯一一个元素，rear也要指向它
    if (size_ == 0) {
      rear_ = head_.get();
    }
    size_++;
  }

};