#ifndef __C_TEMPLATE_LIB_ITERATOR_INTERNAL_INCLUDED_H__
#define __C_TEMPLATE_LIB_ITERATOR_INTERNAL_INCLUDED_H__

#include <stdio.h>
#include "common_internal.h"

// TODO: add length of the pointed container
struct iterator_internal {
	/* ptr to data in memory */
	c_mem_t ptr;

	/* size of pointed data. For internal use */
	size_t size;

	/* ptr position in container. For internal use */
	size_t pos;

	/* length of the container */
	size_t length;
};

// TODO: add length of the pointed container
struct const_iterator_internal {
	/* ptr to data in memory */
	const c_mem_t ptr;

	/* size of pointed data. For internal use */
	size_t size;

	/* ptr position in container. For internal use */
	size_t pos;

	/* length of the container */
	size_t length;
};

typedef struct iterator_internal ii;

#endif // __C_TEMPLATE_LIB_ITERATOR_INTERNAL_INCLUDED_H__
