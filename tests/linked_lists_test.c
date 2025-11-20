#include <stdio.h>
#include "linked_lists.h"

int main() {
   LinkedList *list = linked_list_create();
   for (int i = 0; i<100; i++){
      linked_list_append(list, &i, sizeof(int));
      linked_list_get(list, i);
   }
   for (int i = 0; i<100; i++){
      linked_list_prepend(list, &i, sizeof(int));
   }
   linked_list_clean(list);
   linked_list_get(list, 0);
   linked_list_destroy(list);
}