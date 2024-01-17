#ifndef __C_TEMPLATE_LIB_LIST_INCLUDED_H__
#define __C_TEMPLATE_LIB_LIST_INCLUDED_H__

#include "common.h"
#include <stdio.h>

typedef struct list list_t;

list_t* list_create(size_t size);
void list_insert(list_t* list, void* val, size_t size);
int list_remove(list_t* list, const void* val, void* rmval, int (*remove_fn)(const void* lsval, const void* rmval));
void list_clear(list_t* list);
void list_print(list_t* list, void (*print_fn)(const void* val));
size_t list_size(list_t* list);
void list_delete(list_t* list);

#endif // __C_TEMPLATE_LIB_LIST_INCLUDED_H__
