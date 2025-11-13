#ifndef BNR_LINKED_LIST_H
#define BNR_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;
typedef struct LinkedList LinkedList;

struct Node{
    Node *previous;
    void *data;
    Node *next;
};

struct LinkedList{
    Node *head;
    Node *tail;
    int node_amount;
};


LinkedList *linked_list_create();
Node *node_create(void *data, size_t data_size);

Node *linked_list_get(LinkedList *list, int index);
int linked_list_append(LinkedList *list, void *data, size_t data_size);
int linked_list_prepend(LinkedList *list, void *data, size_t data_size);
int linked_list_destroy(LinkedList *list);
int linked_list_clean(LinkedList *list);
int node_destroy_chain(LinkedList *list, Node *node);



/*
TODOs...

void linked_list_print(LinkedList *list);
int linked_list_healtcheck(LinkedList *list);

*/

#endif