#include "vector.h"
#include "common.h"
#include "common_internal.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 1
#define DEFAULT_GFACTOR 2
#define memalloc(c, s) (c * s)
#define inc_size(v, c) c + (v->opts.chunck_size * v->opts.factor)

struct vector {
	ctl_mem_t mem;
	void *begin;
	void *end;
	size_t length;
	size_t elem_size;
	size_t capacity;
	size_t prev_cap;
	struct vector_options opts;

	/* flag to indicate if the vector is manually resized */
	int resized;
};

static void vector_set_opts(vector_t *vector,
			    const struct vector_options *options)
{
	struct vector_options *vo = &vector->opts;

	if (options) {
		vo->common.allocator = options->common.allocator;
		vo->chunck_size = options->chunck_size;
		vo->factor = options->factor;
	} else {
		vo->common.allocator = malloc;
		vo->chunck_size = DEFAULT_CAPACITY;
		vo->factor = DEFAULT_GFACTOR;
	}
}

vector_t *vector_alloc(size_t elem_size, const struct vector_options *options)
{
	vector_t *v = malloc(sizeof(vector_t));
	if (!v)
		return NULL;

	vector_set_opts(v, options);

	v->mem = NULL;
	v->capacity = 0;
	v->prev_cap = 0;

	v->begin = v->end = v->mem;
	v->length = 0;
	v->elem_size = elem_size;
	v->resized = 0;

	return v;
}

iterator_t vector_begin(const vector_t *vector)
{
	return vector->begin;
}

iterator_t vector_end(const vector_t *vector)
{
	return vector->end;
}

size_t vector_capacity(const vector_t *v)
{
	return v->capacity;
}

void vector_push_back(vector_t *v, void *val, size_t size)
{
	if (v->length == v->capacity) {
		ctl_mem_t newmem = NULL;
		size_t new_cap = 0;

		if (v->resized) {
			while (new_cap < v->length)
				new_cap = inc_size(v, new_cap);
			v->resized = 0;
		} else
			new_cap = inc_size(v, v->capacity);

		newmem = v->opts.common.allocator(memalloc(new_cap, size));
		if (!newmem)
			return;

		memcpy(newmem, v->mem, v->elem_size * v->length);
		v->begin = v->end = newmem;
		v->end += (v->length * v->elem_size);

		free(v->mem);
		v->mem = newmem;
	}

	// __TYPE_CHECK(v->elem_size, size);
	memcpy(v->end, val, v->elem_size);

	v->end += v->elem_size;
	v->length++;
}

int vector_pop_back(vector_t *v, void *rmval)
{
	if (!v->length)
		return 1;

	v->end -= v->elem_size;
	v->length--;

	if (rmval)
		memcpy(rmval, v->end, v->elem_size);

	return 0;
}

int vector_remove(vector_t *vector, const void *val, void *rmval,
		  int (*remove_fn)(const void *vcval, const void *rmval))
{
	return 0;
}

void vector_clear(vector_t *vector)
{
	while (vector->begin != vector->end)
		vector->end -= vector->elem_size;
}

size_t vector_size(const vector_t *vector)
{
	return vector->length;
}

void vector_reserve(vector_t *v, size_t size)
{
	ctl_mem_t newmem = NULL;
	size_t new_size;

	if (v->capacity < v->length + size) {
		new_size = v->length + size;

		newmem = malloc(new_size * v->elem_size);
		if (!newmem)
			return;

		memcpy(newmem, v->mem, v->elem_size * v->length);

		v->begin = v->end = newmem;
		v->end += v->elem_size * v->length;
		v->capacity = new_size;
		v->resized = 1;

		free(v->mem);
		v->mem = newmem;
	}
}

void vector_resize(vector_t *v, size_t size, void *val)
{
	ctl_mem_t newmem = NULL;
	size_t new_size;

	if (v->capacity < size) {
		new_size = v->capacity;
		while (new_size < size)
			new_size = inc_size(v, new_size);

		newmem = v->opts.common.allocator(v->elem_size * new_size);
		if (!newmem)
			return;

		memcpy(newmem, v->mem, v->elem_size * v->length);
		if (val)
			memcpy(newmem + (v->elem_size * v->length), val,
			       v->elem_size * (size - v->capacity));

	} else if (v->capacity > size) {
		new_size = 0;
		while (new_size < size)
			new_size = inc_size(v, new_size);

		newmem = v->opts.common.allocator(v->elem_size * new_size);
		if (!newmem)
			return;

		memcpy(newmem, v->mem, v->elem_size * size);

		if (v->length > size)
			v->length = size;
	} else
		return;

	v->begin = v->end = newmem;
	v->end += v->elem_size * v->length;
	v->capacity = new_size;
	v->resized = 1;

	free(v->mem);
	v->mem = newmem;
}

void vector_shrink_to_fit(vector_t *v)
{
	if (v->capacity > v->length) {
		ctl_mem_t newmem = NULL;

		newmem = v->opts.common.allocator(v->elem_size * v->length);
		if (!newmem)
			return;

		memcpy(newmem, v->mem, v->elem_size * v->length);

		v->begin = v->end = newmem;
		v->end += v->elem_size * v->length;
		v->capacity = v->length;
		v->resized = 1;

		free(v->mem);
		v->mem = newmem;
	}
}

void vector_swap(vector_t *v1, vector_t *v2)
{
	ctl_mem_t tmp;

	tmp = v1->mem;
	v1->mem = v2->mem;
	v2->mem = tmp;
}

void vector_free(vector_t *vector)
{
	free(vector->mem);
	free(vector);
}
