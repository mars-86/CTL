#include "../queue.h"
#include "../common.h"
#include "assert.h"
#include "test.h"

void test_queue(void)
{
    INIT_TEST_ASSERT();

    queue_t* q = queue_create(CTL_VAL_INT, NULL);
    ASSERT_NOT_NULL(q);

    int n;
    size_t len;

    n = 54;
    queue_enqueue(q, CTL_CREATE_VAL(n));
    len = queue_length(q);

    ASSERT_EXPR(len == 1);

    n = 33;
    queue_enqueue(q, CTL_CREATE_VAL(n));
    len = queue_length(q);

    ASSERT_EXPR(len == 2);

    n = 75;
    queue_enqueue(q, CTL_CREATE_VAL(n));
    len = queue_length(q);

    ASSERT_EXPR(len == 3);

    n = 16;
    queue_enqueue(q, CTL_CREATE_VAL(n));
    len = queue_length(q);

    ASSERT_EXPR(len == 4);

    n = 93;
    queue_enqueue(q, CTL_CREATE_VAL(n));
    len = queue_length(q);

    ASSERT_EXPR(len == 5);

    queue_delete(q);
}
