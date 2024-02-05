#include "../vector.h"
#include "../common.h"
#include "assert.h"
#include "test.h"

void test_vector(void)
{
    INIT_TEST_ASSERT();

    vector_t* v = vector_create(CTL_VAL_INT, NULL);
    ASSERT_NOT_NULL(v);

    int n;
    size_t len;

    n = 5;
    vector_push_back(v, CTL_CREATE_VAL(n));
    len = vector_length(v);

    ASSERT_EXPR(len == 1);

    n = 6;
    vector_push_back(v, CTL_CREATE_VAL(n));
    len = vector_length(v);

    ASSERT_EXPR(len == 2);

    n = 3;
    vector_push_back(v, CTL_CREATE_VAL(n));
    len = vector_length(v);

    ASSERT_EXPR(len == 3);

    n = 1;
    vector_push_back(v, CTL_CREATE_VAL(n));
    len = vector_length(v);

    ASSERT_EXPR(len == 4);

    n = 7;
    vector_push_back(v, CTL_CREATE_VAL(n));
    len = vector_length(v);

    ASSERT_EXPR(len == 5);

    iterator_t it;
    for (it = vector_begin(v); it != vector_end(v); MOVE_IT_FWD(v, it))
        ;

    vector_delete(v);
}
