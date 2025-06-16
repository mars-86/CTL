#include "iterator.h"
#include "iterator_internal.h"

struct iterator {
	struct iterator_internal ii;
};

struct const_iterator {
	struct const_iterator_internal cii;
};

struct reverse_iterator {
	struct iterator_internal ii;
};

struct const_reverse_iterator {
	struct iterator_internal cii;
};

void *c_it_data(const iterator_t it)
{
	return it->ii.ptr;
}

void c_it_move(iterator_t it)
{
	iterator_t *_it = &it;
	(*_it)->ii.ptr += (*_it)->ii.size;
}

void c_it_advance(iterator_t it, size_t n)
{
	iterator_t *_it = &it;
	(*_it)->ii.ptr += ((*_it)->ii.size * n);
}

int c_it_distance(const iterator_t first, const iterator_t last)
{
	return last->ii.pos - first->ii.pos;
}

int c_it_position(const iterator_t it)
{
	return it->ii.pos;
}

int c_it_cmp(const iterator_t it1, const iterator_t it2)
{
	if (it1->ii.ptr < it2->ii.ptr)
		return -1;
	else if (it1->ii.ptr > it2->ii.ptr)
		return 1;
	return 0;
}
