#include "vector.h"

#define vector_allocate(type, n, val, opts) \
	vector_alloc(#type, sizeof(type), n, val, opts);
