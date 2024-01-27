#ifndef __C_TEMPLATE_LIB_COMMON_INCLUDED_H__
#define __C_TEMPLATE_LIB_COMMON_INCLUDED_H__

#include <stdio.h>

#define CTL_VAL_POINTER 0
#define CTL_VAL_CHAR sizeof(char)
#define CTl_VAL_SHORT sizeof(short)
#define CTL_VAL_INT sizeof(int)
#define CTL_VAL_FLOAT sizeof(float)
#define CTL_VAL_DOUBLE sizeof(double)
#define CTL_VAL_LONG sizeof(long)

#define CTL_NOT_FREE_PTR 0x0000
#define CTL_FREE_PTR 0x0001

#define CTL_COPY_DATA 0
#define CTL_POINT_DATA 1

#define CTL_CREATE_VAL(v) \
    &v, sizeof(v)

#define CTL_CREATE_VAL_PTR(v) \
    v, CTL_VAL_POINTER

#define CTL_DEREF_DATA(data, type) \
    (*(type*)data)

typedef void* ctl_val_t;
typedef void* (*ctl_allocator_t)(size_t);
typedef int (*ctl_remove_cb_t)(const void* val, const void* rmval);
typedef int (*ctl_delete_cb_t)(const void* val);
typedef struct template_options ctl_tops_t;

struct template_options {
    ctl_allocator_t allocator;
    int flags;
};

#endif // __C_TEMPLATE_LIB_COMMON_INCLUDED_H__
