#ifndef __STACK_H_
#define __STACK_H_

#include "../_data_structures.h"

/**
 * @struct: stack
 * @desc: A stack data structure implementation
 * @param length -> The number of items pushed in the stack
 * @param top -> The index of the item on the top of the stack
 * @param items -> A vector of items
 **/
typedef struct stack {
    size_t length;
    int top;
    vectorT *items;
} stack;

/**
 * @func: stack_create
 * @desc: Creates a basic stack data structure using a dynamic array
 * @return The newly created stack
 **/
stack *stack_create(void);

/**
 * @func: stack_length
 * @desc: Returns the number of elements pushed in the array
 * @param obj -> The typed object containing the stack
 * @return The length (st->length)
 **/
size_t stack_length(stackT *obj);

/**
 * @func: stack_is_empty
 * @desc: Checks whether the stack is empty or not
 * @param obj -> The typed object containing the stack
 * @return A boolean
 **/
int stack_is_empty(stackT *obj);

/**
 * @func: stack_push
 * @desc: Performs a bury operation on the stack
 * @param obj -> The typed object containing the stack
 * @param item -> The item to push to the stack
 **/
void stack_push(stackT *obj, void *item);

/**
 * @func: stack_pop
 * @desc: Performs a pop operation on the stack
 * @param obj -> The typed object containing the stack
 * @return The item on the top of the stack
 **/
void *stack_pop(stackT *obj);

/**
 * @func: stack_peek
 * @desc: Performs a peek operation on the stack
 * @param obj -> The typed object containing the stack
 * @return The item on top of the stack withou removing it
 **/
void *stack_peek(stackT *obj);

/**
 * @func: stack_free
 * @desc: Frees all memory of the stack
 * @param obj -> The typed object containing the stack
 **/
void stack_free(stackT *obj);

#endif