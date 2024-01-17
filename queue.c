#include "queue.h"
#include "common_internal.h"
#include <stdlib.h>
#include <string.h>

typedef struct queue_node queue_node_t;
typedef struct queue_options queue_options_t;

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

queue_t* queue_create(size_t size)
{
    queue_t* __q = (queue_t*)malloc(sizeof(queue_t));

    __q->head = __q->tail = NULL;
    __q->length = 0;
    __q->size = size;

    return __q;
}

void queue_enqueue(queue_t* queue, void* val, size_t size)
{
    __TYPE_CHECK(queue->size, size)
    queue_node_t* __node = (queue_node_t*)malloc(sizeof(queue_node_t));
    __node->val = malloc(queue->size);

    memcpy(__node->val, val, queue->size);
    __node->next = NULL;

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

    if (!__curptr)
        return 1;

    queue->head = __curptr->next;
    if (rmval)
        memcpy(rmval, __curptr->val, queue->size);
    __DELETE_NODE(__curptr);
    queue->length--;

    return 0;
}

void queue_clear(queue_t* queue)
{
    queue_node_t *__curptr, *__nxtptr;
    __curptr = queue->head;

    while (__curptr != NULL) {
        __nxtptr = __curptr->next;
        __DELETE_NODE(__curptr);
        __curptr = __nxtptr;
    }
}

void queue_print(queue_t* queue, void (*print_fn)(const void* val))
{
    queue_node_t* __curptr = queue->head;

    while (__curptr != NULL) {
        print_fn(__curptr->val);
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
