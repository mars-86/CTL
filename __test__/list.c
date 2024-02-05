#include "../list.h"
#include "../common.h"
#include "assert.h"
#include "test.h"
#include <stdio.h>

int rem_val_cb(const void* tval, const void* uval)
{
    return CTL_DEREF_DATA(tval, int) == CTL_DEREF_DATA(uval, int);
}

void handle_val(const void* tval)
{
    (void)tval;
}

void test_list(void)
{
    INIT_TEST_ASSERT();

    list_t* l = list_create(CTL_VAL_INT, NULL);
    ASSERT_NOT_NULL(l);

    int n;
    size_t len;

    n = 0;
    list_insert(l, CTL_CREATE_VAL(n));
    len = list_length(l);

    ASSERT_EXPR(len == 1);

    n = 3;
    list_insert(l, CTL_CREATE_VAL(n));
    len = list_length(l);

    ASSERT_EXPR(len == 2);

    n = 4;
    list_insert(l, CTL_CREATE_VAL(n));
    len = list_length(l);

    ASSERT_EXPR(len == 3);

    n = 9;
    list_insert(l, CTL_CREATE_VAL(n));
    len = list_length(l);

    ASSERT_EXPR(len == 4);

    n = 6;
    list_insert(l, CTL_CREATE_VAL(n));
    len = list_length(l);

    ASSERT_EXPR(len == 5);

    int rmval, rm = 3;
    list_remove(l, &rm, &rmval, rem_val_cb);
    len = list_length(l);

    ASSERT_EXPR(len == 4);

    ASSERT_EXPR(rmval == 3);

    list_for_each(l, handle_val);

    list_delete(l);
}
