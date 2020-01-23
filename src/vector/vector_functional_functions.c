#include "../../headers/_data_structures.h"

vectorT *vector_map(vectorT *obj, lambda modifier) {
    /* In case of invalid inputs */
    if((vector*)obj->value == NULL || modifier == NULL) {
        return NULL;
    }

    /* Create a new vector */
    vectorT *dup = new_vector();

    /* Iterate over the elements */
    for(size_t i = 0; i < vector_length(obj); i++) {
        /* Modify the element and add it to the new vector */
        vector_add(dup, modifier(vector_get(obj, i)));
    }

    /* Return the new vector */
    return dup;
}

vectorT *vector_filter(vectorT *obj, lambda filter) {
    /* In case of invalid inputs */
    if((vector*)obj->value == NULL || filter == NULL) {
        return NULL;
    }

    /* Create a new vector */
    vectorT *dup = new_vector();

    /* Iterate over the elements */
    for(size_t i = 0; i < vector_length(obj); i++) {
        /* Get the item */
        void *item = vector_get(obj, i);

        /* If the item passes the filter */
        if(filter(item)) {
            /* Gets added to the dup vector */
            vector_add(dup, item);
        }
    }
    
    /* Return the new vector */
    return dup;
}

void *vector_reduce(vectorT *obj, lambda fold) {
    /* In case of invalid inputs */
    if((vector*)obj->value == NULL || fold == NULL) {
        return NULL;
    }

    /* Create a duplicate of the vector */
    vectorT *dup = vector_dup(obj);

    /* Create the value than gets returned with the accumulation of the vector elements */
    void *folded_value;

    /* The functionality all lies in the function pointer passed in */
    folded_value = fold(dup);

    /* This function only works as a wrapper */
    return folded_value;
}