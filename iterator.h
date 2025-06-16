#ifndef __C_TEMPLATE_LIB_ITERATOR_INCLUDED_H__
#define __C_TEMPLATE_LIB_ITERATOR_INCLUDED_H__

#include <stdio.h>

typedef struct iterator *iterator_t;
typedef const struct const_iterator *const_iterator_t;

typedef struct reverse_iterator *reverse_iterator_t;
typedef const struct const_reverse_iterator *const_reverse_iterator_t;

void *c_it_data(const iterator_t it);
void c_it_move(iterator_t it);
void c_it_advance(iterator_t it, size_t n);
int c_it_distance(const iterator_t first, const iterator_t last);
int c_it_position(const iterator_t it);
int c_it_cmp(const iterator_t it1, const iterator_t it2);

#endif // __C_TEMPLATE_LIB_ITERATOR_INCLUDED_H__
