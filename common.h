#ifndef __C_TEMPLATE_LIB_COMMON_INCLUDED_H__
#define __C_TEMPLATE_LIB_COMMON_INCLUDED_H__

#define CTL_CREATE_VAL(v) \
    &v, sizeof(v)

#define CTL_DEREF_DATA(data, type) \
    (*(type*)data)

#endif // __C_TEMPLATE_LIB_COMMON_INCLUDED_H__
