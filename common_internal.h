#ifndef __CTL_COMMON_INTERNAL_INCLUDED_H__
#define __CTL_COMMON_INTERNAL_INCLUDED_H__

#include "common.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CTL_FLAG_LLB_MASK 0x000F
#define CTL_FLAG_LHB_MASK 0x00F0
#define CTL_FLAG_HLB_MASK 0x0F00
#define CTL_FLAG_HHB_MASK 0xF000

#define CTL_FREE_MEM(flags) (flags & CTL_FLAG_LLB_MASK & 0x0001)

#define __TYPE_CHECK(a, b)    \
	if (a && b && a != b) \
		return;

#define __DELETE_NODE(node, tsize, tflags, delete_cb)     \
	do {                                              \
		if (delete_cb)                            \
			delete_cb(node->val);             \
		node->next = NULL;                        \
		__ctl_free_val(node->val, tsize, tflags); \
		free(node);                               \
	} while (0)

#define __TEMPLATE_FLAGS(t) (t->opts.common.flags)

#define __TEMPLATE_SET_OPTS(t, opts)                                \
	t->opts.common.allocator = opts && opts->common.allocator ? \
					   opts->common.allocator : \
					   malloc;                  \
	t->opts.common.delete_cb = opts && opts->common.delete_cb ? \
					   opts->common.delete_cb : \
					   NULL;

#define __ALLOC_DATA(allocator, tsz, usz) tsz ? allocator(tsz) : allocator(usz)

struct elem {
	void *data;
};

typedef void *c_data_t;
typedef void *c_mem_t;

inline __attribute__((always_inline)) void
__ctl_assign_val(ctl_val_t *tval, ctl_val_t *uval, c_allocator_t alloc,
		 size_t tsize, size_t usize)
{
	if (usize == C_DATA_SIZE_POINTER) {
		*tval = *uval;
	} else {
		size_t __vsize = tsize ? tsize : usize;
		if (!*tval) {
			*tval = alloc(__vsize);
		} else if (!tsize)
			*tval = realloc(*tval, __vsize);

		memcpy(*tval, *uval, __vsize);
	}
}

inline __attribute__((always_inline)) void
__ctl_free_val(ctl_val_t val, size_t tsize, int tflags)
{
	if (tsize != C_DATA_SIZE_POINTER)
		free(val);
	else if (CTL_FREE_MEM(tflags) == C_FREE_PTR)
		free(val);
}

#endif // __CTL_COMMON_INTERNAL_INCLUDED_H__
