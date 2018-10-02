#include "list.h"
#include "dbg.h"

List *List_create() {
  // Pointer to chunk of memory of size list = List*
  return calloc(1, sizeof(List));
}

void List_destroy(List *list) {
  // how does this work for first next cur?
  LIST_FOREACH(list, first, next, cur) {
    if (cur->prev) {
      free(cur->prev);
    }
  }

  free(list->last);
  free(list);
}

void List_clear(List *list) {

}
