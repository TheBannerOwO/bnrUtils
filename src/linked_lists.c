#include "linked_lists.h"
#include "common_utils.h"

// RAII
// Simplified list to contain only ints.

LinkedList *linked_list_create() {

  LinkedList *list = malloc(sizeof(LinkedList));
  if (!list) return NULL;

  list->head = NULL;
  list->tail = NULL;
  list->node_amount = 0;

  return list;
}

Node *node_create(int data) {

  Node *node = malloc(sizeof(Node));
  if (!node) return NULL;

  node->next = NULL;
  node->previous = NULL;

  node->data = data;

  return node;
}

Node *linked_list_get(LinkedList *list, int index) {

  if (!list || list->node_amount == 0) return NULL;

  Node *node;
  if (index >= 0) {
    if (index > list->node_amount - 1) return NULL;

    // Back -> front
    node = list->tail;

    for (int i = 0; i < index; i++) {
      node = node->next;
    }
  } else {
    index = (-1 * index) - 1;
    if (index > list->node_amount - 1) return NULL;

    // Front -> back
    node = list->head;

    for (int i = 0; i < index; i++) {
      node = node->previous;
    }
  }

  return node;
}

int linked_list_insert(LinkedList *list, int index, int data) {

  if (!list) return RES_INVALIDPARAM;

  if (index == 0) return linked_list_prepend(list, data);

  Node *newNode = node_create(data);
  if (newNode == NULL) return RES_INTERNALERR;

  Node *oldNode = linked_list_get(list, index);
  if (oldNode == NULL) return RES_INTERNALERR;

  Node *previousNode = oldNode->previous;
  previousNode->next = newNode;
  newNode->previous = previousNode;

  newNode->next = oldNode;
  oldNode->previous = newNode;

  list->node_amount++;
  return RES_SUCCESS;
}

int linked_list_append(LinkedList *list, int data) {

  if (!list) return RES_INVALIDPARAM;

  Node *node = node_create(data);

  if (list->node_amount == 0) {
    list->head = node;
    list->tail = node;
  } else if (list->head) {
    node->previous = list->head;
    list->head->next = node;
    list->head = node;
  } else {
    return RES_UNKNOWN;
  }

  list->node_amount++;
  return RES_SUCCESS;
}

int linked_list_prepend(LinkedList *list, int data) {

  if (!list) return RES_INVALIDPARAM;

  Node *node = node_create(data);

  if (list->node_amount == 0) {
    list->head = node;
    list->tail = node;
  } else if (list->tail) {
    node->next = list->tail;
    list->tail->previous = node;
    list->tail = node;
  } else {
    return RES_UNKNOWN;
  }

  list->node_amount++;
  return RES_SUCCESS;
}

int linked_list_clean(LinkedList *list) {

  if (!list) return RES_INVALIDPARAM;
  if (list->node_amount == 0) return RES_SUCCESS;

  Node *node = list->tail;

  list->tail = NULL;
  list->head = NULL;
  list->node_amount = 0;

  while (node->next) {
    node = node->next;
    free(node->previous);
  }
  free(node);

  return RES_SUCCESS;
}

int linked_list_get_destroy(LinkedList *list, int index) {

  if (!list) return RES_INVALIDPARAM;

  Node *node = linked_list_get(list, index);
  if (!node) return RES_INTERNALERR;

  if (node->previous && node->next) {
    node->previous->next = node->next;
    node->next->previous = node->previous;
  } else if (!node->previous) {
    list->tail = node->next;
  } else if (!node->next) {
    list->head = node->previous;
  } else {
    return RES_UNKNOWN;
  }

  free(node);

  return RES_SUCCESS;
}

int linked_list_print(LinkedList *list) {
  if (!list) return RES_INVALIDPARAM;

  Node *node = list->tail;
  if (!node) return RES_INTERNALERR;

  printf("[");
  while (node->next) {
    printf("%d, ", node->data);
    node = node->next;
  }
  printf("%d]\n", node->data);

  return RES_SUCCESS;
}