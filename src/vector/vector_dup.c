#include "../../../cSuite.h"

vector *vector_dup(vector *v) {
    if(v == NULL) return NULL;

    vector *dup;

    if(v->persistence) dup = new_persistent_vector();
    else dup = new_vector();
    
    /* Iteratively copy the vector items from one memory location to another */
    for(size_t i = 0; i < vector_length(v); i++)
        vector_add(dup, vector_get(v, i));

    return dup;
}
