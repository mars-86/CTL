#include "pair.h"
#include "common_internal.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pair_size {
    size_t first;
    size_t second;
};

struct pair {
    ctl_val_t first;
    ctl_val_t second;
    pair_size_t size;
    pair_options_t opts;
};

static void __pair_set_opts(pair_t* pair, pair_options_t* options)
{
    pair->opts.common.allocator = options && options->common.allocator ? options->common.allocator : malloc;
    pair->opts.common.flags = options && options->common.flags ? options->common.flags : 0;
}

pair_t* pair_create(size_t first, size_t second, pair_options_t* options)
{
    pair_t* __p = (pair_t*)malloc(sizeof(pair_t));
    __pair_set_opts(__p, options);

    __p->first = __p->second = NULL;
    __p->size.first = first;
    __p->size.second = second;

    return __p;
}

void pair_set(pair_t* pair, ctl_val_t first, size_t size_first, ctl_val_t second, size_t size_second)
{
    __TYPE_CHECK(pair->size.first, size_first);
    __TYPE_CHECK(pair->size.second, size_second);
    ctl_allocator_t alloc = pair->opts.common.allocator;

    __ctl_assign_val(&pair->first, &first, alloc, pair->size.first, size_first);
    __ctl_assign_val(&pair->second, &second, alloc, pair->size.second, size_second);
}

ctl_val_t pair_first(pair_t* pair)
{
    return pair->first;
}

ctl_val_t pair_second(pair_t* pair)
{
    return pair->second;
}

pair_size_t pair_size(pair_t* pair)
{
    return pair->size;
}

void pair_delete(pair_t* pair)
{
    __ctl_free_val(pair->first, pair->size.first, pair->opts.common.flags);
    __ctl_free_val(pair->second, pair->size.second, pair->opts.common.flags);
    free((pair_t*)pair);
}
