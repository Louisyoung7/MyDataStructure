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

  
};