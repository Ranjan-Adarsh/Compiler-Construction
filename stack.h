/**
MANAF - 2019B3A70351P
ADARSH - 2019B3A70443P
NISHANT - 2019B3A70381P
**/
#ifndef COMPILER_STACK_H
#define COMPILER_STACK_H

#include "function_ptrs.h"
#include <stddef.h>
#include <stdbool.h>
#include "errors.h"
#include "linkedlist.h"

typedef struct Stack {
    size_t element_size;
    size_t size;
    struct LinkedList *linked_list;
} Stack;

struct Stack *create_stack(size_t element_size);

const void *peek_stack(struct Stack *st);

error pop_stack(struct Stack *st, void *address);

error push_stack(struct Stack *st, const void *data);

void print_stack(struct Stack *stack, print_element_ptr printer);

#endif //COMPILER_STACK_H
