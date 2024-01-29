#ifndef __C_TEMPLATE_LIB_QUEUE_INCLUDED_H__
#define __C_TEMPLATE_LIB_QUEUE_INCLUDED_H__

#include "common.h"
#include <stdio.h>

typedef struct queue queue_t;
typedef struct queue_options queue_options_t;

queue_t* queue_create(size_t size, queue_options_t* options);
void queue_enqueue(queue_t* queue, void* val, size_t size);
int queue_dequeue(queue_t* queue, void* rmval);
void queue_clear(queue_t* queue);
void queue_for_each(queue_t* queue, ctl_handle_cb_t cb);
size_t queue_size(queue_t* queue);
size_t queue_length(queue_t* queue);
void queue_delete(queue_t* queue);

#endif // __C_TEMPLATE_LIB_QUEUE_INCLUDED_H__
