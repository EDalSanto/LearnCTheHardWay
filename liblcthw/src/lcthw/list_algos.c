#include "list.h"
#include "list_algos.h"

inline void List_swap(ListNode *node1, ListNode *node2) {
  void *temp = node1->value;
  node1->value = node2->value;
  node2->value = temp;
}

int List_bubble_sort(List *list, List_compare cmp_cb) {
  int swapped = 1;

  while (swapped) {
    swapped = 0;

    LIST_FOREACH(list, first, next, cur) {
      if (cur->next) {
        if (cmp_cb(cur->value, cur->next->value) > 0) {
          List_swap(cur, cur->next);
          swapped = 1;
        }
      }
    }
  }

  return 0;
}

List *List_merge_sort(List *list, List_compare cmp_cb) {
  List *res = List_create();

  return res;
}
