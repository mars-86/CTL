#include "queue.h"
#include "common.h"
#include "common_internal.h"
#include <stdlib.h>
#include <string.h>

typedef struct queue_node queue_node_t;

struct queue_options {
    ctl_tops_t common;
};

struct queue_node {
    void* val;
    queue_node_t* next;
};

struct queue {
    queue_node_t* head;
    queue_node_t* tail;
    size_t length;
    size_t size;
    queue_options_t opts;
};

static void __queue_set_opts(queue_t* queue, queue_options_t* options)
{
    queue->opts.common.allocator = options && options->common.allocator ? options->common.allocator : malloc;
    queue->opts.common.delete_cb = options && options->common.delete_cb ? options->common.delete_cb : NULL;
}

queue_t* queue_create(size_t size, queue_options_t* options)
{
    queue_t* __q = (queue_t*)malloc(sizeof(queue_t));
    __queue_set_opts(__q, options);

    __q->head = __q->tail = NULL;
    __q->length = 0;
    __q->size = size;

    return __q;
}

void queue_enqueue(queue_t* queue, void* val, size_t size)
{
    __TYPE_CHECK(queue->size, size);
    ctl_allocator_t alloc = queue->opts.common.allocator;
    queue_node_t* __node = (queue_node_t*)alloc(sizeof(queue_node_t));

    __node->val = NULL;
    __node->next = NULL;
    __ctl_assign_val(&__node->val, &val, alloc, queue->size, size);

    if (!queue->head) {
        queue->head = __node;
        queue->tail = queue->head;
    } else {
        queue->tail->next = __node;
        queue->tail = queue->tail->next;
    }
    queue->length++;
}

int queue_dequeue(queue_t* queue, void* rmval)
{
    queue_node_t* __curptr = queue->head;
    ctl_delete_cb_t __dcb = queue->opts.common.delete_cb;

    if (!__curptr)
        return 1;

    queue->head = __curptr->next;
    if (rmval)
        memcpy(rmval, __curptr->val, queue->size);
    __DELETE_NODE(__curptr, queue->size, queue->opts.common.flags, __dcb);
    queue->length--;

    return 0;
}

void queue_clear(queue_t* queue)
{
    queue_node_t *__curptr, *__nxtptr;
    ctl_delete_cb_t __dcb = queue->opts.common.delete_cb;
    __curptr = queue->head;

    while (__curptr != NULL) {
        __nxtptr = __curptr->next;
        __DELETE_NODE(__curptr, queue->size, queue->opts.common.flags, __dcb);
        __curptr = __nxtptr;
    }
}

void queue_for_each(queue_t* queue, ctl_handle_cb_t cb)
{
    queue_node_t* __curptr = queue->head;

    while (__curptr != NULL) {
        cb(__curptr->val);
        __curptr = __curptr->next;
    }
}

size_t queue_size(queue_t* queue)
{
    return queue->size;
}

size_t queue_length(queue_t* queue)
{
    return queue->length;
}

void queue_delete(queue_t* queue)
{
    queue_clear(queue);
    free((queue_t*)queue);
}
