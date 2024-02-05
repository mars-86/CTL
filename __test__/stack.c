#include "../stack.h"
#include "../common.h"
#include "assert.h"
#include "test.h"

void test_stack(void)
{
    INIT_TEST_ASSERT();

    stack_t* s = stack_create(CTL_VAL_INT, NULL);
    ASSERT_NOT_NULL(s);

    int n;
    size_t len;

    n = 55;
    stack_push(s, CTL_CREATE_VAL(n));
    len = stack_length(s);

    ASSERT_EXPR(len == 1);

    n = 92;
    stack_push(s, CTL_CREATE_VAL(n));
    len = stack_length(s);

    ASSERT_EXPR(len == 2);

    n = 11;
    stack_push(s, CTL_CREATE_VAL(n));
    len = stack_length(s);

    ASSERT_EXPR(len == 3);

    n = 94;
    stack_push(s, CTL_CREATE_VAL(n));
    len = stack_length(s);

    ASSERT_EXPR(len == 4);

    n = 75;
    stack_push(s, CTL_CREATE_VAL(n));
    len = stack_length(s);

    ASSERT_EXPR(len == 5);

    stack_delete(s);
}
