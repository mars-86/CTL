#include "vector.h"
#include <stdio.h>

int main(void)
{
    vector_t* v = vector_create(sizeof(int), NULL);

    int n;
    n = 5;
    vector_push_back(v, TEMPLATE_VAL(n));

    n = 6;
    vector_push_back(v, TEMPLATE_VAL(n));

    n = 3;
    vector_push_back(v, TEMPLATE_VAL(n));

    n = 1;
    vector_push_back(v, TEMPLATE_VAL(n));

    n = 7;
    vector_push_back(v, TEMPLATE_VAL(n));

    iterator_t it;
    for (it = vector_begin(v); it != vector_end(v); MOVE_IT_FWD(v, it))
        printf("%d\n", TEMPLATE_DEREF_DATA(it, int));

    vector_delete(v);

    return 0;
}
