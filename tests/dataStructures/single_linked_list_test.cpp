#include "dataStructures/single_linked_list.hpp"

using List = SingleLinkedList;

int main() {
  List list1;

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

  // 尾部删除
  list1.popBack();

}