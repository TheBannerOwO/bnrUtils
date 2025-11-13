#include "linked_lists.h"


LinkedList *linked_list_create(){

    LinkedList *list = calloc(1, sizeof(LinkedList));
    if (!list) return NULL;

    return list;
}


Node *node_create(void *data, size_t data_size){

    Node *node = calloc(1, sizeof(Node));
    if (!node) return NULL;

    node->data = malloc(data_size);
    if (!node->data) return NULL;

    memcpy(node->data, data, data_size);

    return node;
}


int linked_list_append(LinkedList* list, void *data, size_t data_size){
    Node *node = node_create(data, data_size);

    if (!list->head){
        list->head = node;
        list->tail = node;
    } else {
        list->head->next = node;
        list->head = node;
    }

    list->node_amount++;
    return 0;
}

int linked_list_prepend(LinkedList* list, void *data, size_t data_size){
    Node *node = node_create(data, data_size);

    if (!list->tail) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->previous = node;
        list->tail = node;
    }

    list->node_amount++;
    return 0;
}

Node *linked_list_get(LinkedList *list, int index){

    if (list->node_amount == 0) return NULL;
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
    if(!list->node_amount){
        free(list);
        return 0;
    }

    Node *tail = list->tail;
    node_destroy_chain(list, tail);
    free(list);

    return 0;
}

int linked_list_clean(LinkedList *list){
    if(!list->node_amount) return 0;

    Node *tail = list->tail;

    node_destroy_chain(list, tail);
    return 0;
}

int node_destroy_chain(LinkedList *list, Node *node){
    if (node->next) node_destroy_chain(list, node->next);
    free(node->data);
    free(node);
    list->node_amount--;
    return 0;
}