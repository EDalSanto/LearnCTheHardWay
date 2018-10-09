#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>
#include "dbg.h"

struct ListNode;

// typedef ListNode so don't have to qualify with struct each time
typedef struct ListNode {
  struct ListNode *next;
  struct ListNode *prev;
  void *value;
} ListNode;

// typedef List so don't have to qualify with struct each time
typedef struct List {
  int count;
  ListNode *first;
  ListNode *last;
} List;

List *List_create();
List *List_copy(List *list);
void List_destroy(List *list);
void List_clear(List *list);
void List_clear_destroy(List *list);

// List Inspections
#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

List *List_join(List *list1, List *list2);
void List_push(List *list, void *value);
void *List_pop(List *list);

void List_unshift(List *list, void *value);
void *List_pop(List *list);

void List_unshift(List *list, void *value);
void *List_shift(List *list);

void *List_remove(List *list, ListNode *node);

// generations all iteration code to loop through each node in list
// relies on fact that list has first pointer and each node has next pointer
#define LIST_FOREACH(L, F, N, C) ListNode *_node = NULL;\
                                                   ListNode *C = NULL;\
for(C = _node = L->F; _node != NULL; C = _node = _node->N)

#endif
