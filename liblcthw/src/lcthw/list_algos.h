#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include <stdlib.h>
#include <lcthw/list.h>

// create a type that is a pointer to a function named List_compare that takes two strings as args
// returns an integer
typedef int (*List_compare) (char *value1, char *value2);

int List_bubble_sort(List *list, List_compare cmp);
List *List_merge(List *left_list, List *right_list, List_compare cmp_cb);
List *List_merge_sort(List *list, List_compare cmp);

#endif
