#ifndef __TEMPLATE_COMMON_INCLUDED_H__
#define __TEMPLATE_COMMON_INCLUDED_H__

#define __TYPE_CHECK(a, b) \
    if (b && a != b)       \
        return;

#define __DELETE_NODE(n) \
    do {                 \
        n->next = NULL;  \
        free(n->val);    \
        free(n);         \
    } while (0)

#endif // __TEMPLATE_COMMON_INCLUDED_H__
