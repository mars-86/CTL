#ifndef __C_TEMPLATE_LIB_VECTOR_INCLUDED_H__
#define __C_TEMPLATE_LIB_VECTOR_INCLUDED_H__

#include "common.h"
#include <stdio.h>

#define IT_MOVE_FWD(t, i) (i += sizeof(v))

#define IT_MOVE_BWD(t, i) (i -= sizeof(v))

struct vector_options {
	ctl_tops_t common;
	size_t chunck_size;
	unsigned int factor;
};

typedef struct vector *vector_t;

// TODO create an iterator data type other than void *
typedef void *iterator_t;
typedef const void *const_iterator_t;

vector_t vector_alloc(size_t size, size_t n, void **val,
		      const struct vector_options *options);

iterator_t vector_begin(const vector_t v);
const_iterator_t vector_cbegin(const vector_t v);
iterator_t vector_end(const vector_t v);
const_iterator_t vector_cend(const vector_t v);
void *vector_at(vector_t v, size_t n);
const void *vector_cat(vector_t v, size_t n);
size_t vector_capacity(const vector_t v);

void vector_push_back(vector_t vector, void *val, size_t size);
int vector_pop_back(vector_t vector, void *rmval);
int vector_remove(vector_t v, iterator_t first, iterator_t last,
		  ctl_delete_cb_t cb);
void vector_clear(vector_t *vector);
void vector_flush(vector_t *vector, ctl_delete_cb_t cb);

void vector_reserve(vector_t v, size_t size);
void vector_resize(vector_t v, size_t new_size, void *val);
void vector_shrink_to_fit(vector_t v);
void vector_swap(vector_t *v1, vector_t *v2);
vector_t vector_dup(vector_t v);

size_t vector_size(const vector_t vector);
size_t vector_length(const vector_t vector);
void vector_free(vector_t vector);

#endif // __C_TEMPLATE_LIB_VECTOR_INCLUDED_H__
