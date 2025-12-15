#include "dataStructures/single_linked_list.hpp"

#include <iostream>
using std::cout;
using std::endl;

int main() {
  SingleLinkedList<int> list1;

  // // 头部添加
  // for (int i = 0; i < 5; ++i) {
  //   list1.prepend(i);
  // }

  // 尾部添加
  for (int i = 0; i < 5; ++i) {
    list1.append(i);
  }

  // // 指定位置添加
  // list1.insert(3, 10);

  // // 头部删除
  // list1.popFront();

  // // 尾部删除
  // list1.popBack();

  // // 指定位置删除
  // list1.popAtIndex(3);

  // // 获取第一个元素
  // cout << list1.getFront() << endl;

  // // 获取最后一个元素
  // cout << list1.getBack() << endl;

  // // 获取指定索引元素
  // cout << list1.get(3) << endl;

  // 修改指定索引的值
  list1.set(4, 10);
}