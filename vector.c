#include "vector.h"
#include "common.h"
#include "common_internal.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __DEFAULT_SIZE 64
#define __MEMALLOC(v, s) ((v->opts.chunck_size * (v->chunks + 1)) * sizeof(s))

typedef struct vector_options vector_options_t;

struct vector_options {
    ctl_tops_t common;
    size_t chunck_size;
};

struct vector {
    ctl_mem_t mem;
    void* begin;
    void* end;
    size_t length;
    size_t size;
    size_t chunks;
    vector_options_t opts;
};

static void __vector_set_opts(vector_t* vector, vector_options_t* options)
{
    vector->opts.common.allocator = options && options->common.allocator ? options->common.allocator : malloc;
    vector->opts.chunck_size = options && options->chunck_size ? options->chunck_size : __DEFAULT_SIZE;
}

/*
static int __resize_vector(vector_t* vector)
{
    ctl_mem_t __newmem = (ctl_mem_t)malloc(__MEMALLOC(vector, vector->size));

    if (!__newmem)
        return 1;

    memcpy(__newmem, vector->mem, vector->opts.chunck_size * vector->chunks * sizeof(vector->size));
    vector->begin = __newmem;
    vector->end = (__newmem + vector->opts.chunck_size * vector->chunks * sizeof(vector->size));
    free(vector->mem);
    vector->mem = __newmem;

    vector->chunks++;

    return 0;
}
*/

iterator_t vector_begin(vector_t* vector)
{
    return vector->begin;
}

iterator_t vector_end(vector_t* vector)
{
    return vector->end;
}

vector_t* vector_create(size_t size, vector_options_t* options)
{
    vector_t* __v = (vector_t*)malloc(sizeof(vector_t));
    __vector_set_opts(__v, options);

    ctl_allocator_t alloc = __v->opts.common.allocator;

    __v->mem = NULL;
    __v->chunks = 0;
    __v->mem = (ctl_mem_t)alloc(__MEMALLOC(__v, size));

    __v->begin = __v->end = __v->mem;
    __v->length = 0;
    __v->size = size;
    __v->chunks++;

    return __v;
}

void vector_push_back(vector_t* vector, void* val, size_t size)
{
    __TYPE_CHECK(vector->size, size);
    memcpy(vector->end, val, vector->size);

    vector->end += vector->size;
    vector->length++;
}

int vector_pop_back(vector_t* vector, void* rmval)
{
    if (vector->end == vector->begin)
        return 1;

    vector->end -= vector->size;
    if (rmval)
        memcpy(rmval, vector->end, vector->size);

    return 0;
}

int vector_remove(vector_t* vector, const void* val, void* rmval, int (*remove_fn)(const void* vcval, const void* rmval))
{
    return 0;
}

void vector_clear(vector_t* vector)
{
    while (vector->begin != vector->end)
        vector->end -= vector->size;
}

size_t vector_size(vector_t* vector)
{
    return vector->size;
}

size_t vector_length(vector_t* vector)
{
    return vector->length;
}

void vector_delete(vector_t* vector)
{
    free((ctl_mem_t)vector->mem);
    free((vector_t*)vector);
}
