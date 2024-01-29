#ifndef __C_TEMPLATE_LIB_LIST_INCLUDED_H__
#define __C_TEMPLATE_LIB_LIST_INCLUDED_H__

#include "common.h"
#include <stdio.h>

typedef struct list list_t;
typedef struct list_options list_options_t;

list_t* list_create(size_t size, list_options_t* options);
void list_insert(list_t* list, void* val, size_t size);
int list_remove(list_t* list, const void* val, void* rmval, ctl_remove_cb_t cb);
void list_clear(list_t* list);
void list_for_each(list_t* list, ctl_handle_cb_t cb);
size_t list_size(const list_t* list);
size_t list_length(const list_t* list);
void list_delete(list_t* list);

#endif // __C_TEMPLATE_LIB_LIST_INCLUDED_H__
