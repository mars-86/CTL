#include "common.h"
#include "list.h"
#include "pair.h"
#include "queue.h"
#include "stack.h"
#include "vector.h"
#include <stdio.h>

void print(const void* v)
{
    int _v = CTL_DEREF_DATA(v, int);
    printf("%d\n", _v);
}

void test_list(void)
{
    printf("LIST\n");
    list_t* l = list_create(sizeof(int), NULL);
    int n;

    n = 0;
    list_insert(l, CTL_CREATE_VAL(n));

    n = 3;
    list_insert(l, CTL_CREATE_VAL(n));

    n = 4;
    list_insert(l, CTL_CREATE_VAL(n));

    n = 9;
    list_insert(l, CTL_CREATE_VAL(n));

    n = 6;
    list_insert(l, CTL_CREATE_VAL(n));

    list_for_each(l, print);
    list_delete(l);
}

void test_stack(void)
{
    printf("STACK\n");
    stack_t* s = stack_create(sizeof(int), NULL);
    int n;

    n = 55;
    stack_push(s, CTL_CREATE_VAL(n));

    n = 92;
    stack_push(s, CTL_CREATE_VAL(n));

    n = 11;
    stack_push(s, CTL_CREATE_VAL(n));

    n = 94;
    stack_push(s, CTL_CREATE_VAL(n));

    n = 75;
    stack_push(s, CTL_CREATE_VAL(n));

    stack_for_each(s, print);
    stack_delete(s);
}

void test_queue(void)
{
    printf("QUEUE\n");
    queue_t* q = queue_create(sizeof(int), NULL);
    int n;

    n = 54;
    queue_enqueue(q, CTL_CREATE_VAL(n));

    n = 33;
    queue_enqueue(q, CTL_CREATE_VAL(n));

    n = 75;
    queue_enqueue(q, CTL_CREATE_VAL(n));

    n = 16;
    queue_enqueue(q, CTL_CREATE_VAL(n));

    n = 93;
    queue_enqueue(q, CTL_CREATE_VAL(n));

    queue_for_each(q, print);
    queue_delete(q);
}

void test_vector(void)
{
    printf("VECTOR\n");
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

void test_pair(void)
{
    printf("PAIR\n");
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
    test_list();
    test_queue();
    test_stack();
    test_vector();
    test_pair();

    return 0;
}
