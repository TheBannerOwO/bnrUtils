#include "linked_lists.h"
#include <stdio.h>

// int test_insertion();

int main() {

  LinkedList *list = linked_list_create();

  for (int i = 0; i < 100; i++) {
    if (i % 2 == 0) {
      linked_list_append(list, i);
    } else {
      linked_list_prepend(list, i);
    }
    linked_list_print(list);
  }

  linked_list_clean(list);
  free(list);
}