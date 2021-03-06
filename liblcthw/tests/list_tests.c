#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>

static List *list = NULL;
char *test1;
char *test2;
char *test3;

void *test_create() {
  list = List_create();
  mu_assert(list != NULL, "Failed to create list");

  return NULL;
}

void *test_clear_destroy() {
  List_clear_destroy(list);

  return NULL;
}

void *test_copy() {
  list = List_create();

  List_push(list, test1);
  List_push(list, test2);

  List *list_copy = List_copy(list);
  mu_assert(list_copy->first->value == test1, "Did not copy test 1 correctly");
  mu_assert(list_copy->first->next->value == test2, "Did not copy test 2 correctly");

  List_clear_destroy(list_copy);

  return NULL;
}

void *test_join() {
  List *list1 = List_create();
  List *list2 = List_create();

  List_push(list1, test1);
  List_push(list2, test2);

  List *joined_list = List_join(list1, list2);
  mu_assert(joined_list->first->value == list1->first->value, "Missing list 1 node");
  mu_assert(joined_list->first->next->value == list2->first->value, "Missing list 2 node");


  return NULL;
}

void *test_push_pop() {
  List_push(list, test1);
  mu_assert(list->last->value == test1, "Wrong value on push");

  List_push(list, test2);
  mu_assert(list->last->value == test2, "Wrong value on push");

  List_push(list, test3);
  mu_assert(list->last->value == test3, "Wrong value on push");

  void *res = List_pop(list);
  mu_assert(res == test3, "Wrong value on pop");

  res = List_pop(list);
  mu_assert(res == test2, "Wrong value on pop");

  res = List_pop(list);
  mu_assert(res == test1, "Wrong value on pop");

  return NULL;
}

void *test_unshift() {
  List_unshift(list, test1);
  mu_assert(list->first->value == test1, "Wrong value on unshift");

  List_unshift(list, test2);
  mu_assert(list->first->value == test2, "Wrong value on unshift");

  List_unshift(list, test3);
  mu_assert(list->first->value == test3, "Wrong value on unshift");

  return NULL;
}

void *test_remove() {
  char *val = List_remove(list, list->first->next);
  mu_assert(val == test2, "Wrong val popped from remove");

  return NULL;
}

int main() {
  mu_suite_start();

  test1 = (char*)malloc(100);
  test2 = (char*)malloc(100);
  test3 = (char*)malloc(100);

  strcpy(test1, "test1 data");
  strcpy(test2, "test2 data");
  strcpy(test3, "test3 data");

  mu_run_test(test_create);
  mu_run_test(test_push_pop);
  mu_run_test(test_copy);
  mu_run_test(test_join);
  mu_run_test(test_unshift);
  mu_run_test(test_remove);
}
