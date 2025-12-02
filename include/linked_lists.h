#ifndef BNR_LINKED_LIST_H
#define BNR_LINKED_LIST_H

#include "common_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;
typedef struct LinkedList LinkedList;

struct Node {
  Node *previous;
  int data;
  Node *next;
};

struct LinkedList {
  Node *head;
  Node *tail;
  int node_amount;
};

/**
 * Returns a pointer to a linked list without nodes.
 *
 * @return LinkedList* pointer to the created list
 */
LinkedList *linked_list_create();

/**
 * Returns a pointer to a fresh node with only the data given stored.
 *
 * @param data value to be stored
 * @return Node* pointer to the created node
 */
Node *node_create(int data);

/**
 * Returns a pointer to the node at the given index, on
 * the given list. Index starts at 0 just like arrays, can
 * also take negative values to do a backwards search from
 * the head towards the tail.
 * Eg: if (index = -1) then the last node is returned.
 *
 * @param list the list to search in
 * @param index position of the objective node
 * @return Node* the node at the i-th position.
 */
Node *linked_list_get(LinkedList *list, int index);

/**
 * Inserts a node at the given position,
 * pushing the existing one forward.
 *
 * @param list list to insert to
 * @param index where to place the new node
 * @param data value for the new node
 * @return function exit status
 */
int linked_list_insert(LinkedList *list, int index, int data);

/**
 * Gets the node at the given index on the list (see linked_list_get
 * for more info), re-orders the list based on the nodes left if any,
 * and then frees up the node at the original i-th place.
 *
 * @param list list to search and remove from
 * @param index position of the node to destroy
 * @return function exit status
 */
int linked_list_get_destroy(LinkedList *list, int index);

/**
 * Appends a node with the given value to the list.
 *
 * @param list the list to append to
 * @param data the value to copy into the node
 * @return function exit status
 */
int linked_list_append(LinkedList *list, int data);

/**
 * Prepends a node with the given value to the list.
 *
 * @param list - the list to prepend to
 * @param data value for the new node
 * @return function exit status
 */
int linked_list_prepend(LinkedList *list, int data);

/**
 * Frees all the nodes and removes them from the list.
 *
 * @param LinkedList* list - list to be cleaned
 * @return function exit status
 */
int linked_list_clean(LinkedList *list);

/**
 * Prints all the values in the list in order,
 * from tail to head.
 *
 * @param list
 * @return function exit status
 */
int linked_list_print(LinkedList *list);
/*
TODOs...

int linked_list_healtcheck(LinkedList *list);

*/

#endif