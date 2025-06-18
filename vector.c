#include "vector.h"
#include "common.h"
#include "common_internal.h"
#include "iterator.h"
#include "iterator_internal.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 1
#define DEFAULT_GFACTOR 2
#define memalloc(v, c, s) (v->opts.common.allocator(c * s))
#define inc_size(v, c) (c + (v->opts.chunck_size * v->opts.factor))

#define rm_internal(v, rcb)                          \
	do {                                         \
		while (v->end.ptr != v->begin.ptr) { \
			rcb(v->end.ptr);             \
			v->end.ptr -= v->size;       \
		}                                    \
		rcb(v->end.ptr);                     \
	} while (0)

#define rm_elems_cb(v, cb) rm_internal(v, cb)

#define rm_elems(v) rm_internal(v, v->opts.common.delete_cb)

#define init_vec_props(v, c, l, r) \
	do {                       \
		v->capacity = c;   \
		v->length = l;     \
		v->resized = r;    \
	} while (0)

#define set_begin_iterator(v, mem, n)           \
	do {                                    \
		v->_begin.ptr = mem;            \
		v->_begin.size = v->size;       \
		v->_begin.pos = 0;              \
		v->begin = v->_begin;           \
		v->rend = v->_rend = v->_begin; \
	} while (0)

#define set_end_iterator(v, mem, n)               \
	do {                                      \
		v->_end.ptr = mem;                \
		v->_end.size = v->size;           \
		v->_end.pos = n;                  \
		v->_end.ptr += (v->size * n);     \
		v->end = v->_end;                 \
		v->rbegin = v->_rbegin = v->_end; \
	} while (0)

#define set_iterators(v, mem, n)               \
	do {                                   \
		set_begin_iterator(v, mem, n); \
		set_end_iterator(v, mem, n);   \
	} while (0)

struct vector {
	/* vector memory, here the elements are stored */
	c_mem_t mem;

	/* iterator to the first element of the vector */
	ii begin;

	/* iterator to the back of the last element of the vector */
	ii end;

	/* internal iterator to the first element of the vector */
	ii _begin;

	/* internal iterator to the back of the last element of the vector */
	ii _end;

	/* reverse iterator to the back of the last element of the vector */
	ii rbegin;

	/* reverse iterator to the first element of the vector */
	ii rend;

	/* internal reverse iterator to the back of the last element of the vector */
	ii _rbegin;

	/* internal reverse iterator to the first element of the vector */
	ii _rend;

	/* the amount of elements in the vector */
	size_t length;

	/* this var has the type of vector element */
	const char *type;

	/* this var has the size in bytes of vector element */
	size_t size;

	/* this var holds the memory allocated by the vector */
	size_t capacity;

	/* set the vector options i.e. allocator, callbacks. */
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
		vo->gfactor = options->gfactor;
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
		vo->gfactor = DEFAULT_GFACTOR;
		vo->factor = 1;
	}
}

vector_t vector_alloc(const char *type, size_t size, size_t n, void **val,
		      const struct vector_options *options)
{
	vector_t v = NULL;
	c_mem_t newmem = NULL;

	v = malloc(sizeof(struct vector));
	if (!v)
		return NULL;

	if (n > 0) {
		newmem = malloc(n * size);
		if (!newmem)
			return NULL;

		init_vec_props(v, n, 0, 1);
	} else if (val) {
		int i;
		for (i = 0; *(val + i) != NULL; ++i)
			;

		newmem = malloc(i * size);
		if (!newmem)
			return NULL;

		init_vec_props(v, i, i, 1);
	} else {
		newmem = malloc(size);
		if (!newmem)
			return NULL;

		init_vec_props(v, 1, 0, 0);
	}

	vector_set_opts(v, options);

	v->mem = newmem;
	v->size = size;

	set_iterators(v, v->mem, v->length);

	return v;
}

void vector_begin(const vector_t v, iterator_t it)
{
	struct iterator_internal **_it = (struct iterator_internal **)&it;

	(*_it)->ptr = v->begin.ptr;
	(*_it)->pos = v->begin.pos;
	(*_it)->size = v->begin.size;
	(*_it)->length = v->length;
}

void vector_end(const vector_t v, iterator_t it)
{
	struct iterator_internal **_it = (struct iterator_internal **)&it;

	(*_it)->ptr = v->end.ptr;
	(*_it)->pos = v->end.pos;
	(*_it)->size = v->end.size;
	(*_it)->length = v->length;
}

const_iterator_t vector_cbegin(const vector_t v)
{
	v->begin = v->_begin;
	return (const_iterator_t)&v->begin;
}

const_iterator_t vector_cend(const vector_t v)
{
	v->end = v->_end;
	return (const_iterator_t)&v->end;
}

reverse_iterator_t vector_rbegin(const vector_t v)
{
	v->rbegin = v->_rbegin;
	return (reverse_iterator_t)&v->rbegin;
}

reverse_iterator_t vector_rend(const vector_t v)
{
	v->rend = v->_rend;
	return (reverse_iterator_t)&v->rend;
}

void *vector_at(vector_t v, size_t n)
{
	if (n > v->length - 1)
		return NULL;

	return v->mem + (n * v->size);
}

const void *vector_cat(vector_t v, size_t n)
{
	if (n > v->length - 1)
		return NULL;

	return (const void *)(v->mem + (n * v->size));
}

size_t vector_capacity(const vector_t v)
{
	return v->capacity;
}

void *vector_front(vector_t v)
{
	if (!v->length)
		return NULL;

	return v->begin.ptr;
}

void *vector_back(vector_t v)
{
	if (!v->length)
		return NULL;

	return v->end.ptr - v->size;
}

void *vector_head(vector_t v)
{
	return v->begin.ptr;
}

void *vector_tail(vector_t v)
{
	return v->end.ptr - v->size;
}

int vector_empty(const vector_t v)
{
	return v->length ? 0 : 1;
}

int vector_push_back(vector_t v, void *val, const char *type)
{
	/*
	 * if we do not pass the value by reference and we do not copy the value at the very begining and
	 * we execute another sentences, we lost the reference to the value
	 */
	unsigned char *p = (unsigned char *)val;
	memcpy(v->_end.ptr, p, v->size);

	v->length++;

#ifdef _DEBUG
	printf("v->length: %ld\nv->capacity: %ld\n", v->length, v->capacity);
#endif

	if (v->length == v->capacity) {
		c_mem_t newmem = NULL;
		size_t new_cap = 0;

		if (v->resized) {
			while (new_cap < v->length) {
				new_cap = inc_size(v, new_cap);
				v->opts.factor *= v->opts.gfactor;
			}
			v->resized = 0;
		} else {
			new_cap = inc_size(v, v->capacity);
			v->opts.factor *= v->opts.gfactor;
		}

		newmem = realloc(v->mem, new_cap * v->size);
		if (!newmem)
			return -1;

		v->mem = newmem;
		v->capacity = new_cap;

		set_iterators(v, v->mem, v->length);
	} else {
		v->_end.pos = v->length;
		v->_end.ptr += v->size;
		v->end = v->_end;
		v->rbegin = v->_rbegin = v->_end;
	}

	return 0;
}

int vector_pop_back(vector_t v, void *rmval)
{
	if (!v->length)
		return 1;

	v->length--;

	v->_end.ptr -= v->size;
	v->end = v->_end;
	v->rbegin = v->_rbegin = v->_end;

	if (rmval)
		memcpy(rmval, v->end.ptr, v->size);
	else if (v->opts.common.delete_cb)
		v->opts.common.delete_cb(v->end.ptr);

	return 0;
}

int vector_erase(vector_t v, iterator_t first, iterator_t last)
{
	c_mem_t newmen = NULL;
	struct iterator_internal *_first = (struct iterator_internal *)first;
	struct iterator_internal *_last = (struct iterator_internal *)last;

	if (_first->pos == (v)->_end.pos || _last->pos < _first->pos ||
	    _last->pos == 0)
		return 0;

	newmen = memalloc(v, v->capacity, v->size);
	if (!newmen)
		return -1;

	printf("first pos: %ld\n", _first->pos);
	printf("last pos: %ld\n", _last->pos);

	size_t newlen = v->length - (_last->pos - _first->pos) - 1;
	printf("Vector newlen: %ld\n", newlen);

	if (v->_begin.pos == _first->pos) {
		memcpy(newmen, _last->ptr + v->size,
		       (v->_end.pos - _last->pos) * v->size);
	} else {
		memcpy(newmen, v->_begin.ptr, _first->pos * v->size);
		memcpy(newmen + (_first->pos * v->size), _last->ptr + v->size,
		       (v->_end.pos - _last->pos - 1) * v->size);
	}

	if (v->opts.common.delete_cb) {
		while (_first->pos < _last->pos) {
			v->opts.common.delete_cb(_first->ptr);
			c_it_advance((iterator_t)_first, (v->size));
		}
	}

	free(v->mem);

	v->mem = newmen;
	v->length = newlen;

	set_iterators(v, v->mem, v->length);

	return 0;
}

int vector_erase_at(vector_t v, iterator_t position)
{
	return vector_erase(v, position, position);
}

int vector_remove(vector_t v, iterator_t first, iterator_t last,
		  ctl_delete_cb_t cb)
{
	c_mem_t newmen = NULL;

	newmen = memalloc(v, v->capacity, v->size);
	if (!newmen)
		return -1;

	if (v->_begin.ptr == first) {
		while (first != last)
			c_it_move(first);
	}

	while (first != last) {
		cb(first);
		c_it_advance(first, v->size);
	}

	return 0;
}

int vector_remove_at(vector_t v, iterator_t position, ctl_delete_cb_t cb)
{
	c_mem_t newmen = NULL;

	newmen = memalloc(v, v->capacity, v->size);
	if (!newmen)
		return -1;

	cb(position);

	return 0;
}

void vector_clear(vector_t *v)
{
	if ((*v)->opts.common.delete_cb)
		rm_elems((*v));
	else
		(*v)->end = (*v)->begin;

	(*v)->length = 0;
}

void vector_flush(vector_t *v, ctl_delete_cb_t cb)
{
	rm_elems_cb((*v), cb);
	(*v)->length = 0;
}

size_t vector_size(const vector_t v)
{
	return v->length;
}

void vector_assign(vector_t v, size_t n, void *val, const char *type)
{
	c_mem_t newmem = NULL;

	if (!val)
		return;

	if (v->capacity < n) {
		newmem = memalloc(v, v->size, n);
		if (!newmem)
			return;

		memcpy(newmem, val, v->size * n);

		if (v->opts.common.delete_cb)
			rm_elems(v);

		free(v->mem);
		v->mem = newmem;

		set_iterators(v, newmem, n);

		v->capacity = v->length = n;
		v->resized = 1;
	} else {
		if (v->opts.common.delete_cb)
			rm_elems(v);

		memcpy(v->mem, val, v->size * n);

		v->_end.ptr += (v->size * n);
		v->end = v->_end;
	}
}

void vector_reserve(vector_t v, size_t n)
{
	c_mem_t newmem = NULL;
	size_t new_size;

	if (v->capacity < v->length + n) {
		new_size = v->length + n;

		newmem = malloc(new_size * v->size);
		if (!newmem)
			return;

		memcpy(newmem, v->mem, v->size * v->length);

		free(v->mem);
		v->mem = newmem;

		set_iterators(v, v->mem, new_size);

		v->capacity = new_size;
		v->resized = 1;
	}
}

void vector_resize(vector_t v, size_t n, void *val, const char *type)
{
	c_mem_t newmem = NULL;
	size_t new_size;

	if (v->capacity < n) {
		new_size = v->capacity;
		while (new_size < n)
			new_size = inc_size(v, new_size);

		newmem = v->opts.common.allocator(v->size * new_size);
		if (!newmem)
			return;

		memcpy(newmem, v->mem, v->size * v->length);
		if (val)
			memcpy(newmem + (v->size * v->length), val,
			       v->size * (n - v->capacity));

	} else if (v->capacity > n) {
		new_size = 0;
		while (new_size < n)
			new_size = inc_size(v, new_size);

		newmem = v->opts.common.allocator(v->size * new_size);
		if (!newmem)
			return;

		memcpy(newmem, v->mem, v->size * n);

		if (v->length > n)
			v->length = n;
	} else
		return;

	free(v->mem);
	v->mem = newmem;

	set_iterators(v, v->mem, v->length);

	v->capacity = new_size;
	v->resized = 1;
}

void vector_shrink_to_fit(vector_t v)
{
	if (v->capacity > v->length) {
		c_mem_t newmem = NULL;

		newmem = v->opts.common.allocator(v->size * v->length);
		if (!newmem)
			return;

		memcpy(newmem, v->mem, v->size * v->length);

		set_iterators(v, v->mem, v->length);

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

vector_t vector_dup(const vector_t v)
{
	vector_t _v = vector_alloc(v->type, v->size, v->length, NULL,
				   (const struct vector_options *)&v->opts);

	if (!_v)
		return NULL;

	memcpy(_v->mem, v->mem, v->length * v->size);

	set_iterators(_v, _v->mem, v->length);

	_v->capacity = _v->length = v->length;
	_v->resized = 1;

	return _v;
}

void vector_free(vector_t v)
{
	if (v->opts.common.delete_cb)
		rm_elems(v);
	free(v->mem);
	free(v);
}

void vector_delete(vector_t v, ctl_delete_cb_t cb)
{
	vector_t *_v = &v;

	rm_elems_cb((*_v), cb);
	free((*_v)->mem);
	free(*_v);
}
