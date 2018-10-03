#include "list.h"
#include "dbg.h"

List *List_create() {
  // Pointer to chunk of memory of size list = List*
  return calloc(1, sizeof(List));
}

void List_clear_destroy(List *list) {
  check(list != NULL, "List can't be NULL");

  LIST_FOREACH(list, first, next, cur) {
    if (cur->prev) {
      free(cur->prev);
      free(cur->value);
    }
  }

  free(list->last);
  free(list);

error:
  return;
}

void List_push(List *list, void *value) {
  check(list != NULL, "List can't be NULL");

  ListNode *node = calloc(1, sizeof(ListNode));

  node->value = value;

  if (list->last == NULL) {
    list->first = node;
    list->last = node;
  } else {
    list->last->next = node;
    node->prev = list->last;
    list->last = node;
  }

  list->count++;

error:
  return;
}

void *List_pop(List *list) {
  check(list != NULL, "List can't be NULL");

  ListNode *node = list->last;

  if (node != NULL) {
    return List_remove(list, node);
  } else {
    return NULL;
  }

error:
  return NULL;
}

void List_unshift(List *list, void *value) {
  check(list != NULL, "List can't be NULL");

  ListNode *node = calloc(1, sizeof(ListNode));
  node->value = value;

  if (list->first == NULL) {
    list->first = node;
    list->last = node;
  } else {
    list->first->prev = node;
    node->next = list->first;
    list->first = node;
  }

  list->count++;

error:
  return;
}

void *List_shift(List *list) {
  check(list != NULL, "List can't be NULL");

  ListNode *node = list->first;

  if (node != NULL) {
    return List_remove(list, node);
  } else {
    return NULL;
  }


error:
  return NULL;
}

void *List_remove(List *list, ListNode *node) {
  check(list != NULL, "List can't be NULL");

  void *result = NULL;

  check(list->first && list->last, "List is empty");
  check(node, "node can't be null");

  if (node == list->first && node == list->last) {
    // single node list
    list->first = NULL;
    list->last = NULL;
  } else if (node == list->first) {
    list->first = node->next;
    check(list->first != NULL, "Invalid list, somehow got a first that is NULL");

    list->first->prev = NULL;
  } else if (node == list->last) {
    list->last = node->prev;
    check(list->last != NULL, "Invalid list, somehow got a first that is NULL");
    list->last->next = NULL;
  } else { // middle node
    ListNode *after = node->next;
    ListNode *before = node->prev;

    after->prev = before;
    before->next = after;
  }

  list->count--;
  result = node->value;
  free(node);

  return result;

error:
  return NULL;
}
