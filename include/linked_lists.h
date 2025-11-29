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
  void *data;
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
 * Returns a pointer to a new node with all its values set to NULL.
 *
 * @param void* data - pointer to the data to be stored in the node
 * @param size_t data_size - size of the data to be stored in the node
 * @return Node* pointer to the created node
 */
Node *node_create(void *data, size_t data_size);

/**
 * Returns a pointer to the node at the given index, on
 * the given list. Index starts at 0 just like arrays, can
 * also take negative values to do a backwards search from
 * the end towards the beginning.
 * Eg: if (index = -1) the last node is returned.
 *
 * @param LinkedList* list - the list to search in
 * @param int index - position of the objective node
 * @return Node* the node at the i-th position.
 */
Node *linked_list_get(LinkedList *list, int index);

/**
 * Gets the node at the given index on the list (see linked_list_get
 * for more info), re-orders the list based on the nodes left if any,
 * and then frees up the node at the original i-th place.
 *
 * @param LinkedList* list - list to search and remove from
 * @param int index -
 * @return int
 */
int linked_list_get_destroy(LinkedList *list, int index);

/**
 * Copies the data at the given address, creates a new node with a deep copy
 * (given that the objective data isnt a pointer itself), and appends it to
 * the list.
 *
 * @param LinkedList* list - the list to append to
 * @param void* data - data to copy into the new node
 * @param size_t data_size - size of the given data
 * @return function exit status
 */
int linked_list_append(LinkedList *list, void *data, size_t data_size);

/**
 * Copies the data at the given address, creates a new node with a deep copy
 * (given that the objective data isnt a pointer itself), prepends it to the
 * list.
 *
 * @param LinkedList* list - the list to prepend to
 * @param void* data - data to copy into the new node
 * @param size_t data_size - size of the given data
 * @return function exit status
 */
int linked_list_prepend(LinkedList *list, void *data, size_t data_size);

/**
 * Frees all the nodes, their data, and the list.
 * Returns the function exit status
 *
 * @param LinkedList* list - list to be destroyed
 * @return int function exit status
 */
int linked_list_destroy(LinkedList *list);

/**
 * Frees all the nodes and their data
 * and removes them from the list.
 *
 * @param LinkedList* list - list to be cleaned
 * @return int function exit status
 */
int linked_list_clean(LinkedList *list);

/*
TODOs...

void linked_list_print(LinkedList *list);
int linked_list_healtcheck(LinkedList *list);

*/

#endif