#include "headers/linked_list_functional_functions.h"

linked_list *linked_list_map(linked_list *list, linked_list_lambda modifier) {
    if(list == NULL || modifier == NULL) return NULL;

    linked_list *dup = new_linked_list();

    /* Typecast and use the address to take advantage of a pointer to pointer approach */
    llnode **probe = &(list->head);

    /* Dereference once */
    while(*probe) {
        void *item = (*probe)->item;
        linked_list_add(dup, modifier(item));

        /* Point probe to the next node */
        probe = (llnode**)&(*probe)->next;
    }

    return dup;
}

linked_list *linked_list_filter(linked_list *list, linked_list_lambda filter) {
    if(list == NULL || filter == NULL) return NULL;

    linked_list *dup = new_linked_list();

    /* Typecast and use the address to take advantage of a pointer to pointer approach */
    llnode **probe = &(list->head);

    /* Dereference once */
    while(*probe) {
        void *item = (*probe)->item;
        if(filter(item))
            linked_list_add(dup, item);

        /* Point probe to the next node */
        probe = (llnode**)&(*probe)->next;
    }

    return dup;
}

void *linked_list_reduce(linked_list *list, linked_list_lambda fold) {
    if(list == NULL || fold == NULL) return NULL;

    llnode **probe = (&list->head);

    /* Get the initial value */
    /* Create the value that gets returned with the accumulation of the vector elements */
    void *accumulator = (*probe)->item;

    /* Start counting from the next */
    probe = (llnode**)&(*probe)->next;

    while(*probe) {
        void *current = (*probe)->item;
        accumulator = fold(accumulator, current);
        probe = (llnode**)&(*probe)->next;
    }
    
    return accumulator;
}
