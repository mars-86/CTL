#ifndef __C_TEMPLATE_LIB_STACK_INCLUDED_H__
#define __C_TEMPLATE_LIB_STACK_INCLUDED_H__

#include "common.h"
#include <stdio.h>

typedef struct stack stack_t;
typedef struct stack_options stack_options_t;

stack_t* stack_create(size_t size, stack_options_t* options);
void stack_push(stack_t* stack, void* val, size_t size);
int stack_pop(stack_t* stack, void* rmval);
void stack_clear(stack_t* stack);
void stack_for_each(stack_t* stack, ctl_handle_cb_t cb);
size_t stack_size(stack_t* stack);
size_t stack_length(stack_t* stack);
void stack_delete(stack_t* stack);

#endif // __C_TEMPLATE_LIB_STACK_INCLUDED_H__
