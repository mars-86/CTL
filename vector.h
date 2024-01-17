#ifndef __CTL_VECTOR_INCLUDED_H__
#define __CTL_VECTOR_INCLUDED_H__

#include <stdio.h>

#define TEMPLATE_VAL(v) \
    &v, sizeof(v)

#define MOVE_IT_FWD(v, i) \
    (i += vector_size(v))

#define MOVE_IT_BWD(v, i) \
    (i -= vector_size(v))

#define TEMPLATE_DEREF_DATA(data, type) \
    (*(type*)data)

typedef struct vector vector_t;
typedef struct vector_options vector_options_t;
typedef const void* iterator_t;

iterator_t vector_begin(vector_t* vector);
iterator_t vector_end(vector_t* vector);
vector_t* vector_create(size_t size, vector_options_t* options);
void vector_push_back(vector_t* vector, void* val, size_t size);
int vector_pop_back(vector_t* vector, void* rmval);
int vector_remove(vector_t* vector, const void* val, void* rmval, int (*remove_fn)(const void* vcval, const void* rmval));
void vector_clear(vector_t* vector);
size_t vector_size(vector_t* vector);
size_t vector_length(vector_t* vector);
void vector_delete(vector_t* vector);

#endif // __CTL_VECTOR_INCLUDED_H__
