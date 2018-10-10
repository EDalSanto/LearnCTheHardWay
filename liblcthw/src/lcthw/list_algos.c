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
  // don't merge sort empty list
  if (list->count <= 1) {
      return list;
  }

  // recursive case: first divide the list into equal-size sublists
  // consisting of the first half and second half of the list
  List *left_list = List_create();
  List *right_list = List_create();
  int middle = list->count / 2;
  LIST_FOREACH(list, first, next, cur) {
    // get to middle
    if (middle > 0) { // even -> add to left
      List_push(left_list, cur->value);
    } else { // odd -> add to right
      List_push(right_list, cur->value);
    }

    middle--;
  }
  // sort each sublist
  left_list = List_merge_sort(left_list, cmp_cb);
  right_list = List_merge_sort(right_list, cmp_cb);

  // put lists back together
  List *result = List_merge(left_list, right_list, cmp_cb);

  List_destroy(left_list);
  List_destroy(right_list);

  return result;
}

List *List_merge(List *left_list, List *right_list, List_compare cmp_cb) {
  List *merged_list = List_create();
  void *value = NULL;

  // nodes in either list
  while (left_list->count > 0 && right_list->count > 0) {
    // pick lowest from each one
    if (cmp_cb(left_list->first->value, right_list->first->value) < 0) {
      // left side less than right -> add left
      value = List_shift(left_list);
      List_push(merged_list, value);
    } else { // right side less than left -> add right
      value = List_shift(right_list);
      List_push(merged_list, value);
    }
  }

  // either lists may still have nodes
  // consume them while they do
  // only 1 loop will execute
  while (left_list->count > 0) {
    value = List_shift(left_list);
    List_push(merged_list, value);
  }
  while (right_list->count > 0) {
    value = List_shift(right_list);
    List_push(merged_list, value);
  }

  return merged_list;
}
