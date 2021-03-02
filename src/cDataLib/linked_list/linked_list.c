#include "headers/linked_list.h"

linked_list *linked_list_create(void) {
    linked_list *list = (linked_list*)malloc(sizeof(linked_list));
    list->head = NULL;
    list->length = 0;
    return list;
}

void linked_list_add(linked_list *list, void *item) {
    if(list == NULL || item == NULL) return;

    /* Use the address to take advantage of a pointer to pointer approach */
    llnode **probe = &(list->head);

    /* Create a new node */
    llnode *newnode = (llnode*)malloc(sizeof(llnode));
    newnode->item = (void*)malloc(sizeof(item));
    newnode->item = item;

    /* Traverse to the end of the linked list */
    while(*probe)
        probe = (llnode**)&(*probe)->next;

    newnode->next = (struct llnode*)*probe;
    *probe = newnode;
    list->length++;
}

void linked_list_remove(linked_list *list, void *item) {
    if(list == NULL || item == NULL) return;

    llnode **probe = &(list->head);

    while((*probe) && (*probe)->item != list)
        probe = (llnode**)&(*probe)->next;

    *probe = (llnode*)((*probe)->next);
}
