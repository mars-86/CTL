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

#define c_deref_data(type, data) (data ? (*(type *)data) : 0)
#define c_cast_ptr(type, data) (data ? ((type *)data) : NULL)

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
	c_data_deallocator_t data_dealloc;

	/* container flags */
	int flags;
};

static inline char *c_data_int8(char n)
{
	char *_n = &n;
	return _n;
}

static inline unsigned char *c_data_uint8(unsigned char n)
{
	unsigned char *_n = &n;
	return _n;
}

static inline short *c_data_int16(short n)
{
	short *_n = &n;
	return _n;
}

static inline unsigned short *c_data_uint16(unsigned short n)
{
	unsigned short *_n = &n;
	return _n;
}

static inline int *c_data_int32(int n)
{
	int *_n = &n;
	return _n;
}

static inline unsigned int *c_data_uint32(unsigned int n)
{
	unsigned int *_n = &n;
	return _n;
}

static inline long *c_data_long64(long n)
{
	long *_n = &n;
	return _n;
}

static inline unsigned long *c_data_ulong64(unsigned long n)
{
	unsigned long *_n = &n;
	return _n;
}

static inline float *c_data_float(float n)
{
	float *_n = &n;
	return _n;
}

static inline double *c_data_double(double n)
{
	double *_n = &n;
	return _n;
}

#endif // __C_TEMPLATE_LIB_COMMON_INCLUDED_H__
