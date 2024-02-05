#include "../pair.h"
#include "../common.h"
#include "assert.h"
#include "test.h"

void test_pair(void)
{
    INIT_TEST_ASSERT();

    pair_t* p = pair_create(CTL_VAL_INT, CTL_VAL_INT, NULL);
    ASSERT_NOT_NULL(p);

    int n1 = 3, n2 = 7;

    pair_set(p, CTL_CREATE_VAL(n1), CTL_CREATE_VAL(n2));

    // printf("%d\n", CTL_DEREF_DATA(pair_first(p), int));
    // printf("%d\n", CTL_DEREF_DATA(pair_second(p), int));

    pair_t* p2 = pair_create(CTL_VAL_POINTER, CTL_VAL_INT, NULL);

    n1 = 5;
    pair_set(p2, CTL_CREATE_VAL_PTR("Hello, world!"), CTL_CREATE_VAL(n1));

    // printf("%s\n", (char*)pair_first(p2));
    // printf("%d\n", CTL_DEREF_DATA(pair_second(p2), int));

    pair_delete(p);
    pair_delete(p2);
}
