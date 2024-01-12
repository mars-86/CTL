#ifndef __TEMPLATE_STACK_INCLUDED_H__
#define __TEMPLATE_STACK_INCLUDED_H__

#include <stdio.h>

#define TEMPLATE_VAL(v) \
    &v, sizeof(v)

typedef struct stack stack_t;

stack_t* stack_create(size_t size);
void stack_push(stack_t* stack, void* val, size_t size);
int stack_pop(stack_t* stack, void* rmval);
void stack_clear(stack_t* stack);
void stack_print(stack_t* stack, void (*print_fn)(const void* val));
size_t stack_size(stack_t* stack);
void stack_delete(stack_t* stack);

#endif // __TEMPLATE_STACK_INCLUDED_H__
