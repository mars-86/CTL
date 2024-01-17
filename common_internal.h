#ifndef __CTL_COMMON_INTERNAL_INCLUDED_H__
#define __CTL_COMMON_INTERNAL_INCLUDED_H__

#include <stdio.h>

#define __TYPE_CHECK(a, b) \
    if (b && a != b)       \
        return;

#define __DELETE_NODE(n) \
    do {                 \
        n->next = NULL;  \
        free(n->val);    \
        free(n);         \
    } while (0)

typedef void* ctl_mem_t;
typedef struct template_options ctl_tops_t;

struct template_options {
    void* (*allocator)(size_t size);
};

#endif // __CTL_COMMON_INTERNAL_INCLUDED_H__
