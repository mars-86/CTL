#ifndef __C_TEMPLATE_LIB_COMMON_INCLUDED_H__
#define __C_TEMPLATE_LIB_COMMON_INCLUDED_H__

#include <stdio.h>

#define C_DATA_SIZE_POINTER sizeof(NULL)
#define C_DATA_SIZE_CHAR sizeof(char)
#define C_DATA_SIZE_SHORT sizeof(short)
#define C_DATA_SIZE_INT sizeof(int)
#define C_DATA_SIZE_FLOAT sizeof(float)
#define C_DATA_SIZE_DOUBLE sizeof(double)
#define C_DATA_SIZE_LONG sizeof(long)

#define C_DATA_TYPE_CHAR "char"
#define C_DATA_TYPE_SHORT "short"
#define C_DATA_TYPE_INT "int"
#define C_DATA_TYPE_FLOAT "float"
#define C_DATA_TYPE_DOUBLE "double"
#define C_DATA_TYPE_LONG "long"

#define C_NOT_FREE_PTR 0x0000
#define C_FREE_PTR 0x0001

#define C_DATA_CPY 0
#define C_DATA_REF 1

#define c_create_data(v) &v, sizeof(v)

#define c_create_data_ptr(v) v, C_DATA_SIZE_POINTER

#define c_deref_data(type, data) (*(type *)data)

typedef void *ctl_val_t;
typedef void *(*c_allocator_t)(size_t);
typedef void (*c_deallocator_t)(void *__ptr);
typedef void *(*c_data_allocator_t)(size_t);
typedef void (*c_data_deallocator_t)(void *__ptr);
typedef void (*ctl_handle_cb_t)(const void *val);
typedef int (*ctl_remove_cb_t)(const void *val, const void *rmval);
typedef int (*ctl_delete_cb_t)(void *val);
typedef struct template_options ctl_tops_t;

struct template_options {
	/* container allocator */
	c_allocator_t allocator;

	/* container deallocator */
	c_deallocator_t deallocator;

	/* container data allocator */
	c_data_allocator_t data_alloc;

	/* container data deallocator */
	c_data_allocator_t data_dealloc;

	/* TODO remove this*/
	ctl_delete_cb_t delete_cb;

#ifdef C_RT_DATA_TYPE_CHECK
	/* for data type checking at run-time */
	char *data_typ;
#endif
	/* container flags */
	int flags;
};

#endif // __C_TEMPLATE_LIB_COMMON_INCLUDED_H__
