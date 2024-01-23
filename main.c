#include "common.h"
#include "pair.h"
#include "vector.h"
#include <stdio.h>

void test_vector(void)
{
    vector_t* v = vector_create(sizeof(int), NULL);
    int n;

    n = 5;
    vector_push_back(v, CTL_CREATE_VAL(n));

    n = 6;
    vector_push_back(v, CTL_CREATE_VAL(n));

    n = 3;
    vector_push_back(v, CTL_CREATE_VAL(n));

    n = 1;
    vector_push_back(v, CTL_CREATE_VAL(n));

    n = 7;
    vector_push_back(v, CTL_CREATE_VAL(n));

    iterator_t it;
    for (it = vector_begin(v); it != vector_end(v); MOVE_IT_FWD(v, it))
        printf("%d\n", CTL_DEREF_DATA(it, int));

    printf("length: %lu\n", vector_length(v));

    vector_delete(v);
}

void test_pair(pair_t* p3)
{
    pair_t* p = pair_create(CTL_VAL_INT, CTL_VAL_INT, NULL);

    int n1 = 3, n2 = 7;

    pair_set(p, CTL_CREATE_VAL(n1), CTL_CREATE_VAL(n2));

    printf("%d\n", CTL_DEREF_DATA(pair_first(p), int));
    printf("%d\n", CTL_DEREF_DATA(pair_second(p), int));

    pair_t* p2 = pair_create(CTL_VAL_POINTER, CTL_VAL_INT, NULL);

    n1 = 5;
    pair_set(p2, CTL_CREATE_VAL_PTR("Hello, world!"), CTL_CREATE_VAL(n1));

    printf("%s\n", (char*)pair_first(p2));
    printf("%d\n", CTL_DEREF_DATA(pair_second(p2), int));

    pair_delete(p);
    pair_delete(p2);
}

int main(void)
{
    test_vector();
    pair_t* p = NULL;
    test_pair(p);

    // printf("%s\n", (char*)pair_first(p));
    // printf("%d\n", CTL_DEREF_DATA(pair_second(p), int));

    // pair_delete(p);

    return 0;
}
