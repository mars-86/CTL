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

#define CTL_FREE_MEM(flags) \
    (flags & CTL_FLAG_LLB_MASK & 0x0001)

#define __TYPE_CHECK(a, b) \
    if (a && b && a != b)  \
        return;

#define __DELETE_NODE(node, delete_cb) \
    do {                               \
        if (delete_cb)                 \
            delete_cb(node->val);      \
        node->next = NULL;             \
        free(node->val);               \
        free(node);                    \
    } while (0)

#define __ALLOC_DATA(allocator, tsz, usz) \
    tsz ? allocator(tsz) : allocator(usz)

typedef void* ctl_mem_t;

inline __attribute__((always_inline)) void __ctl_assign_val(ctl_val_t* tval, ctl_val_t* uval, ctl_allocator_t alloc, size_t tsize, size_t usize)
{
    if (usize == CTL_VAL_POINTER) {
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

inline __attribute__((always_inline)) void __ctl_free_val(ctl_val_t val, size_t tsize, int tflags)
{
    if (tsize != CTL_VAL_POINTER)
        free(val);
    else if (CTL_FREE_MEM(tflags) == CTL_FREE_PTR)
        free(val);
}

#endif // __CTL_COMMON_INTERNAL_INCLUDED_H__
