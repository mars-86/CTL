#ifndef __C_TEMPLATE_LIB_PAIR_INCLUDED_H__
#define __C_TEMPLATE_LIB_PAIR_INCLUDED_H__

#include "common.h"
#include <stdio.h>

struct pair_options {
    ctl_tops_t common;
};

typedef struct pair pair_t;
typedef struct pair_options pair_options_t;
typedef struct pair_size pair_size_t;

pair_t* pair_create(size_t size_first, size_t size_second, pair_options_t* options);
void pair_set(pair_t* pair, ctl_val_t val_first, size_t size_first, ctl_val_t val_second, size_t size);
ctl_val_t pair_first(pair_t* pair);
ctl_val_t pair_second(pair_t* pair);
pair_size_t pair_size(pair_t* pair);
void pair_delete(pair_t* pair);

#endif // __C_TEMPLATE_LIB_PAIR_INCLUDED_H__
