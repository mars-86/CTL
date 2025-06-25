#ifndef __C_TEMPLATE_LIB_VECTOR_INCLUDED_H__
#define __C_TEMPLATE_LIB_VECTOR_INCLUDED_H__

#include "common.h"
#include "iterator.h"
#include <stdio.h>

#define C_ALLOC_NULL_VECTOR 0

#define it_move_fwd(v, i) (i += vector_size(v))

#define it_move_bwd(v, i) (i -= vector_size(v))

#define vector_alloc_empty(type, opts) \
	vector_alloc(#type, sizeof(type), C_ALLOC_NULL_VECTOR, NULL, opts)

#define vector_alloc_n(type, n, opts) \
	vector_alloc(#type, sizeof(type), n, NULL, opts)

#define vector_alloc_val(type, val, opts) \
	vector_alloc(#type, sizeof(type), C_ALLOC_NULL_VECTOR, val, opts)

#define vector_push_back_m(v, val, type) vector_push_back(v, val, #type)

#define vector_resize_n(v, n) vector_resize(v, n, NULL, NULL)

#define vector_resize_val(v, n, val, type) vector_resize(v, n, val, #type)

#define vector_assign_m(v, n, val, type) vector_assign(v, n, val, #type);

struct vector_options {
	ctl_tops_t common;
	size_t chunck_size;
	unsigned int factor;
	unsigned int gfactor;
};

typedef struct vector *vector_t;

extern vector_t vector_alloc(const char *type, size_t size, size_t n,
			     void **val, const struct vector_options *options);

extern void vector_begin(const vector_t __restrict__ v, iterator_t it)
	__attribute__((leaf)) __attribute__((nonnull(1, 2)));

extern void vector_end(const vector_t __restrict__ v, iterator_t it)
	__attribute__((leaf)) __attribute__((nonnull(1, 2)));

extern void vector_cend(const vector_t __restrict__ v, const_iterator_t it)
	__attribute__((leaf)) __attribute__((nonnull(1, 2)));

extern void vector_cbegin(const vector_t __restrict__ v, const_iterator_t it)
	__attribute__((leaf)) __attribute__((nonnull(1, 2)));

extern void vector_rbegin(const vector_t __restrict__ v, reverse_iterator_t it)
	__attribute__((leaf)) __attribute__((nonnull(1, 2)));

extern void vector_rend(const vector_t __restrict__ v, reverse_iterator_t it)
	__attribute__((leaf)) __attribute__((nonnull(1, 2)));

extern void *vector_at(vector_t v, size_t n) __attribute__((leaf));
extern const void *vector_cat(vector_t v, size_t n) __attribute__((leaf));
extern size_t vector_capacity(const vector_t v) __attribute__((leaf));
extern int vector_empty(const vector_t v) __attribute__((leaf));
extern void *vector_front(vector_t v) __attribute__((leaf));
extern void *vector_back(vector_t v) __attribute__((leaf));
extern void *vector_head(vector_t v) __attribute__((leaf));
extern void *vector_tail(vector_t v) __attribute__((leaf));

extern int vector_push_back(vector_t __restrict__ v, void *__restrict__ val,
			    const char *__restrict__ type)
	__attribute__((nonnull(1, 2)));

extern int vector_pop_back(vector_t __restrict__ v, void *__restrict__ rmval)
	__attribute__((nonnull(1)));

extern int vector_erase(vector_t v, iterator_t first, iterator_t last);
extern int vector_remove(vector_t v, iterator_t first, iterator_t last,
			 c_data_deallocator_t cb);
extern void vector_clear(vector_t v);
extern void vector_flush(vector_t v, c_data_deallocator_t cb);

extern int vector_assign(vector_t v, size_t n, void *val, const char *type);
extern void vector_reserve(vector_t v, size_t size);
extern void vector_resize(vector_t v, size_t new_size, void *val,
			  const char *type);
extern int vector_shrink_to_fit(vector_t v);
extern void vector_swap(vector_t *v1, vector_t *v2);
extern vector_t vector_dup(vector_t v);

extern size_t vector_size(const vector_t v);
extern size_t vector_length(const vector_t v);
extern void vector_free(vector_t v);
extern void vector_delete(vector_t v, c_data_deallocator_t cb);

#endif // __C_TEMPLATE_LIB_VECTOR_INCLUDED_H__
