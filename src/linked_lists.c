#include "linked_lists.h"
#include "common_utils.h"


LinkedList *linked_list_create(){

    LinkedList *list = malloc(sizeof(LinkedList));
    if (!list) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->node_amount = 0;

    return list;
}


Node *node_create(void *data, size_t data_size){

    if (data_size <= 0 || !data) return NULL;

    Node *node = calloc(1, sizeof(Node));
    if (!node) return NULL;

    node->next = NULL;
    node->previous = NULL;

    node->data = malloc(data_size);
    if (!node->data) return NULL;

    memcpy(node->data, data, data_size);

    return node;
}


int linked_list_append(LinkedList *list, void *data, size_t data_size){

    if (data_size <= 0 || !list || !data) return RES_INVALIDPARAM;

    Node *node = node_create(data, data_size);

    
    if (!list->head){
        list->head = node;
        list->tail = node;
    } else {
        node->previous = list->head;
        list->head->next = node;
        list->head = node;
    }

    list->node_amount++;
    return RES_SUCCESS;
}


int linked_list_prepend(LinkedList *list, void *data, size_t data_size){

    if (data_size <= 0 || !list || !data) return RES_INVALIDPARAM;

    Node *node = node_create(data, data_size);

    
    if (!list->tail) {
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->tail;
        list->tail->previous = node;
        list->tail = node;
    }

    list->node_amount++;
    return RES_SUCCESS;
}


Node *linked_list_get(LinkedList *list, int index){

    if (!list || list->node_amount == 0) return NULL;
    Node *node;

    if (index >= 0){
        if (index > list->node_amount - 1) return NULL;

        node = list->tail;

        for (int i = 0; i < index; i++){
            node = node->next;
        }
    } else {
        index = (-1*index) - 1;
        if (index > list->node_amount - 1) return NULL;

        node = list->head;

        for (int i = 0; i < index; i++){
            node = node->previous;
        }
    }

    return node;
}


int linked_list_destroy(LinkedList *list){
    if (!list) return RES_INVALIDPARAM;

    if (!list->node_amount){
        free(list);
        return RES_SUCCESS;
    }

    node_list_destroy(list);
    free(list);

    return RES_SUCCESS;
}


int linked_list_clean(LinkedList *list){
    if (!list) return RES_INVALIDPARAM;
    if (!list->node_amount) return RES_SUCCESS;

    node_list_destroy(list);
    return RES_SUCCESS;
}


int node_list_destroy(LinkedList *list){

    if (!list->node_amount || 
        !list->tail || 
        !list->head ||
        !list) return RES_INVALIDPARAM;

    Node *node = list->tail;

    // Detaching node chain from list
    list->tail = NULL;
    list->head = NULL;
    
    for (int i = 0; i < list->node_amount; i++){
        free(node->data);
        
        if (node->next) {
            node = node->next;
            free(node->previous);
        } else {
            free(node);
        }
    }

    list->node_amount = 0;

    // OLD RECURSIVE IMPLEMENTATION
    // if (node->next) node_list_destroy(list, node->next);
    // free(node->data);
    // free(node);

    return RES_SUCCESS;
}


int linked_list_get_destroy(LinkedList *list, int index){

    if (!list) return RES_INVALIDPARAM;

    Node *node = linked_list_get(list, index);

    if (node->previous && node->next) {
        // Dont break the chain
        node->previous->next = node->next;
        node->next->previous = node->previous;
    } else if (!node->previous) {
        list->tail = node->next;
    } else if (!node->next) {
        list->head = node->previous;
    } else {
        return RES_UNKNOWN;
    }

    free(node->data);
    free(node);

    return RES_SUCCESS;
}