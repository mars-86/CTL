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

iterator_t it_alloc(void)
{
	iterator_t it = malloc(sizeof(struct iterator));
	if (!it)
		return NULL;

	return it;
}

void *c_it_data(const iterator_t it)
{
	return it->ii.ptr;
}

void c_it_move(iterator_t it)
{
	it->ii.ptr += it->ii.size;
	it->ii.pos++;
}

void c_it_advance(iterator_t it, size_t n)
{
	it->ii.ptr += (it->ii.size * n);
	it->ii.pos += n;
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

void it_free(iterator_t it)
{
	free(it);
}

void *c_rit_data(const reverse_iterator_t rit)
{
	return rit->ii.ptr;
}

void c_rit_move(reverse_iterator_t rit)
{
	reverse_iterator_t *_rit = &rit;
	(*_rit)->ii.ptr -= (*_rit)->ii.size;
	(*_rit)->ii.pos--;
}

void c_rit_advance(reverse_iterator_t rit, size_t n)
{
	reverse_iterator_t *_rit = &rit;
	(*_rit)->ii.ptr -= ((*_rit)->ii.size * n);
	(*_rit)->ii.pos -= n;
}

int c_rit_distance(const reverse_iterator_t first,
		   const reverse_iterator_t last)
{
	return first->ii.pos - last->ii.pos;
}

int c_rit_position(const reverse_iterator_t rit)
{
	return rit->ii.pos;
}

int c_rit_cmp(const reverse_iterator_t it1, const reverse_iterator_t it2)
{
	if (it2->ii.ptr < it1->ii.ptr)
		return -1;
	else if (it2->ii.ptr > it1->ii.ptr)
		return 1;
	return 0;
}
