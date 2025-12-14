#include "dataStructures/single_linked_list.hpp"

using List = SingleLinkedList;

int main() {
  List list1;

  // 头部添加
  for (int i = 0; i < 5; ++i) {
    list1.prepend(i);
  }

}