#include "stack.h"
#include "common_internal.h"
#include <stdlib.h>
#include <string.h>

typedef struct stack_node stack_node_t;

struct stack_options {
    ctl_tops_t common;
};

struct stack_node {
    void* val;
    stack_node_t* next;
};

struct stack {
    stack_node_t* top;
    stack_node_t* bottom;
    size_t length;
    size_t size;
    stack_options_t opts;
};

static void __stack_set_opts(stack_t* stack, stack_options_t* options)
{
    stack->opts.common.allocator = options && options->common.allocator ? options->common.allocator : malloc;
    stack->opts.common.delete_cb = options && options->common.delete_cb ? options->common.delete_cb : NULL;
}

stack_t* stack_create(size_t size, stack_options_t* options)
{
    stack_t* __s = (stack_t*)malloc(sizeof(stack_t));
    __stack_set_opts(__s, options);

    __s->top = __s->bottom = NULL;
    __s->length = 0;
    __s->size = size;

    return __s;
}

void stack_push(stack_t* stack, void* val, size_t size)
{
    __TYPE_CHECK(stack->size, size);
    ctl_allocator_t alloc = stack->opts.common.allocator;
    stack_node_t* __node = (stack_node_t*)alloc(sizeof(stack_node_t));

    __node->val = NULL;
    __node->next = NULL;
    __ctl_assign_val(&__node->val, &val, alloc, stack->size, size);

    if (!stack->top) {
        stack->top = __node;
        stack->bottom = stack->top;
    } else {
        __node->next = stack->top;
        stack->top = __node;
    }
    stack->length++;
}

int stack_pop(stack_t* stack, void* rmval)
{
    stack_node_t* __curptr = stack->top;
    ctl_delete_cb_t __dcb = stack->opts.common.delete_cb;

    if (!__curptr)
        return 1;

    stack->top = __curptr->next;
    if (rmval)
        memcpy(rmval, __curptr->val, stack->size);
    __DELETE_NODE(__curptr, stack->size, stack->opts.common.flags, __dcb);
    stack->length--;

    return 0;
}

void stack_clear(stack_t* stack)
{
    stack_node_t *__curptr, *__nxtptr;
    ctl_delete_cb_t __dcb = stack->opts.common.delete_cb;
    __curptr = stack->top;

    while (__curptr != NULL) {
        __nxtptr = __curptr->next;
        __DELETE_NODE(__curptr, stack->size, stack->opts.common.flags, __dcb);
        __curptr = __nxtptr;
    }
}

void stack_for_each(stack_t* stack, ctl_handle_cb_t cb)
{
    stack_node_t* __curptr = stack->top;

    while (__curptr != NULL) {
        cb(__curptr->val);
        __curptr = __curptr->next;
    }
}

size_t stack_size(stack_t* stack)
{
    return stack->size;
}

size_t stack_length(stack_t* stack)
{
    return stack->length;
}

void stack_delete(stack_t* stack)
{
    stack_clear(stack);
    free((stack_t*)stack);
}
