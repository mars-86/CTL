#include "vector.h"
#include "common.h"
#include "common_internal.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 1
#define DEFAULT_GFACTOR 2
#define memalloc(v, c, s) (v->opts.common.allocator(c * s))
#define inc_size(v, c) c + (v->opts.chunck_size * v->opts.factor)
#define del_elems(v)                                      \
	do {                                              \
		while (v->end != v->begin) {              \
			v->opts.common.delete_cb(v->end); \
			v->end -= v->elem_size;           \
		}                                         \
		v->opts.common.delete_cb(v->end);         \
	} while (0)

struct vector {
	ctl_mem_t mem;
	void *begin;
	void *end;
	size_t length;
	size_t elem_size;
	size_t capacity;
	struct vector_options opts;

	/* flag to indicate if the vector is manually resized */
	int resized;
};

static void vector_set_opts(vector_t vector,
			    const struct vector_options *options)
{
	struct vector_options *vo = &vector->opts;

	if (options) {
		vo->chunck_size = options->chunck_size;
		vo->factor = options->factor;
		if (options->common.allocator)
			vo->common.allocator = options->common.allocator;
		else
			vo->common.allocator = malloc;

		if (options->common.delete_cb)
			vo->common.delete_cb = options->common.delete_cb;
		else
			vo->common.delete_cb = NULL;
	} else {
		vo->common.allocator = malloc;
		vo->common.delete_cb = NULL;
		vo->chunck_size = DEFAULT_CAPACITY;
		vo->factor = DEFAULT_GFACTOR;
	}
}

vector_t vector_alloc(size_t size, const struct vector_options *options)
{
	vector_t v = malloc(sizeof(vector_t));
	if (!v)
		return NULL;

	vector_set_opts(v, options);

	v->mem = NULL;
	v->capacity = 0;
	v->begin = v->end = v->mem;
	v->length = 0;
	v->elem_size = size;
	v->resized = 0;

	return v;
}

iterator_t vector_begin(const vector_t v)
{
	return v->begin;
}

iterator_t vector_end(const vector_t v)
{
	return v->end;
}

size_t vector_capacity(const vector_t v)
{
	return v->capacity;
}

void vector_push_back(vector_t v, void *val, size_t size)
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

		newmem = memalloc(v, new_cap, size);
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

int vector_pop_back(vector_t v, void *rmval)
{
	if (!v->length)
		return 1;

	v->end -= v->elem_size;
	v->length--;

	if (rmval)
		memcpy(rmval, v->end, v->elem_size);
	else if (v->opts.common.delete_cb)
		v->opts.common.delete_cb(v->end);

	return 0;
}

const void *vector_at(vector_t v, size_t n)
{
	if (n > v->length - 1)
		return NULL;

	return v->mem + (n * v->elem_size);
}

int vector_remove(vector_t v, const void *val, void *rmval,
		  int (*remove_fn)(const void *vcval, const void *rmval))
{
	return 0;
}

void vector_clear(vector_t *v)
{
	if ((*v)->opts.common.delete_cb)
		del_elems((*v));
	else
		(*v)->end = (*v)->begin;

	(*v)->length = 0;
}

size_t vector_size(const vector_t v)
{
	return v->length;
}

void vector_assign(vector_t v, size_t n, void *val)
{
	ctl_mem_t newmem = NULL;

	if (!val)
		return;

	if (v->capacity < n) {
		newmem = memalloc(v, v->elem_size, n);
		if (!newmem)
			return;

		memcpy(newmem, val, v->elem_size * n);

		if (v->opts.common.delete_cb)
			del_elems(v);

		v->begin = v->end = newmem;
		v->end += v->elem_size * n;
		v->capacity = v->length = n;
		v->resized = 1;

		free(v->mem);
		v->mem = newmem;
	} else {
		if (v->opts.common.delete_cb)
			del_elems(v);

		memcpy(v->mem, val, v->elem_size * n);

		v->end += (v->elem_size * n);
	}
}

void vector_reserve(vector_t v, size_t n)
{
	ctl_mem_t newmem = NULL;
	size_t new_size;

	if (v->capacity < v->length + n) {
		new_size = v->length + n;

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

void vector_resize(vector_t v, size_t n, void *val)
{
	ctl_mem_t newmem = NULL;
	size_t new_size;

	if (v->capacity < n) {
		new_size = v->capacity;
		while (new_size < n)
			new_size = inc_size(v, new_size);

		newmem = v->opts.common.allocator(v->elem_size * new_size);
		if (!newmem)
			return;

		memcpy(newmem, v->mem, v->elem_size * v->length);
		if (val)
			memcpy(newmem + (v->elem_size * v->length), val,
			       v->elem_size * (n - v->capacity));

	} else if (v->capacity > n) {
		new_size = 0;
		while (new_size < n)
			new_size = inc_size(v, new_size);

		newmem = v->opts.common.allocator(v->elem_size * new_size);
		if (!newmem)
			return;

		memcpy(newmem, v->mem, v->elem_size * n);

		if (v->length > n)
			v->length = n;
	} else
		return;

	v->begin = v->end = newmem;
	v->end += v->elem_size * v->length;
	v->capacity = new_size;
	v->resized = 1;

	free(v->mem);
	v->mem = newmem;
}

void vector_shrink_to_fit(vector_t v)
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
	vector_t tmp = NULL;

	tmp = *v1;
	v1 = v2;
	*v2 = tmp;
}

void vector_free(vector_t v)
{
	if (v->opts.common.delete_cb)
		del_elems(v);
	free(v->mem);
	free(v);
}
