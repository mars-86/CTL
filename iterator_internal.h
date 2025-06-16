#ifndef __C_TEMPLATE_LIB_ITERATOR_INTERNAL_INCLUDED_H__
#define __C_TEMPLATE_LIB_ITERATOR_INTERNAL_INCLUDED_H__

#include <stdio.h>
#include "common_internal.h"

struct iterator_internal {
	/* ptr to data in memory */
	c_mem_t ptr;

	/* size of pointed data. For internal use */
	size_t size;

	/* ptr position in container. For internal use */
	int pos;
};

struct const_iterator_internal {
	/* ptr to data in memory */
	const c_mem_t ptr;

	/* size of pointed data. For internal use */
	size_t size;

	/* ptr position in container. For internal use */
	int pos;
};

typedef struct iterator_internal ii;

#endif // __C_TEMPLATE_LIB_ITERATOR_INTERNAL_INCLUDED_H__
