#include "../vector.h"
#include "../common.h"
#include "assert.h"
#include "test.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

char *c_data_int8(char n)
{
	char *_n = &n;
	return _n;
}

unsigned char *c_data_uint8(unsigned char n)
{
	unsigned char *_n = &n;
	return _n;
}

short *c_data_int16(short n)
{
	short *_n = &n;
	return _n;
}
unsigned short *c_data_uint16(unsigned short n)
{
	unsigned short *_n = &n;
	return _n;
}

int *c_data_int32(int n)
{
	int *_n = &n;
	return _n;
}

unsigned int *c_data_uint32(unsigned int n)
{
	unsigned int *_n = &n;
	return _n;
}

long *c_data_long64(long n)
{
	long *_n = &n;
	return _n;
}

unsigned long *c_data_ulong64(unsigned long n)
{
	unsigned long *_n = &n;
	return _n;
}

float *c_data_float(float n)
{
	float *_n = &n;
	return _n;
}

double *c_data_double(double n)
{
	double *_n = &n;
	return _n;
}

void add_values()
{
}

void test_vector_push_back(void)
{
	INIT_TEST_ASSERT();

	vector_t v = vector_alloc_empty(int, NULL);

	ASSERT_NOT_NULL(v);

	size_t len;

	void *p = c_data_int32(4);

	printf("PTR: %d\n", 1);
	printf("PTR: %d\n", *(int *)p);

	vector_push_back_m(v, c_data_int32(-5), int);
	len = vector_size(v);

	ASSERT_EXPR(len == 1);

	printf("PTR: %d\n", *(int *)p);

	vector_push_back_m(v, c_data_int32(6), int);
	len = vector_size(v);

	ASSERT_EXPR(len == 2);

	vector_push_back_m(v, c_data_int32(3), int);
	len = vector_size(v);

	ASSERT_EXPR(len == 3);

	vector_push_back_m(v, c_data_int32(-1), int);
	len = vector_size(v);

	ASSERT_EXPR(len == 4);

	vector_push_back_m(v, c_data_int32(7), int);
	len = vector_size(v);

	ASSERT_EXPR(len == 5);

	vector_push_back_m(v, c_data_int32(3), int);
	len = vector_size(v);

	ASSERT_EXPR(len == 6);

	vector_push_back_m(v, c_data_int32(8), int);
	len = vector_size(v);

	ASSERT_EXPR(len == 7);

	iterator_t it, it2, it3, it4;

	it = it_alloc();
	it2 = it_alloc();
	it3 = it_alloc();
	it4 = it_alloc();

	vector_begin(v, it);

	printf("%d\n", c_deref_data(int, c_it_data(it)));

	c_it_move(it);

	printf("%d\n", c_deref_data(int, c_it_data(it)));

	vector_begin(v, it2);

	printf("%d\n\n", c_deref_data(int, c_it_data(it)));

	for (vector_begin(v, it3), vector_end(v, it4); c_it_cmp(it3, it4);
	     c_it_move(it3))
		printf("%d\n", c_deref_data(int, c_it_data(it3)));

	for (vector_begin(v, it3), vector_end(v, it4); c_it_cmp(it3, it4);
	     c_it_move(it3))
		printf("%d\n", c_deref_data(int, c_it_data(it3)));

	vector_free(v);
}

void test_vector_pop_back(void)
{
	INIT_TEST_ASSERT();

	vector_t v = vector_alloc(C_DATA_TYPE_INT, C_DATA_SIZE_INT,
				  C_ALLOC_NULL_VECTOR, NULL, NULL);
	ASSERT_NOT_NULL(v);

	size_t len;
	int rval;

	vector_push_back(v, c_data_int32(-5), C_DATA_TYPE_INT);
	len = vector_size(v);

	ASSERT_EXPR(len == 1);

	vector_push_back(v, c_data_int32(6), C_DATA_TYPE_INT);
	len = vector_size(v);

	ASSERT_EXPR(len == 2);

	vector_pop_back(v, NULL);
	len = vector_size(v);

	ASSERT_EXPR(len == 1);

	vector_pop_back(v, NULL);
	len = vector_size(v);

	ASSERT_EXPR(len == 0);

	vector_pop_back(v, NULL);
	len = vector_size(v);

	ASSERT_EXPR(len == 0);

	vector_push_back(v, c_data_int32(3), C_DATA_TYPE_INT);
	len = vector_size(v);

	ASSERT_EXPR(len == 1);

	vector_push_back(v, c_data_int32(7), C_DATA_TYPE_INT);
	len = vector_size(v);

	ASSERT_EXPR(len == 2);

	vector_push_back(v, c_data_int32(8), C_DATA_TYPE_INT);
	len = vector_size(v);

	ASSERT_EXPR(len == 3);

	vector_pop_back(v, &rval);
	len = vector_size(v);

	ASSERT_EXPR(rval == 8);
	ASSERT_EXPR(len == 2);

	vector_pop_back(v, NULL);
	len = vector_size(v);

	ASSERT_EXPR(len == 1);

	vector_push_back(v, c_data_int32(9), C_DATA_TYPE_INT);
	len = vector_size(v);

	ASSERT_EXPR(len == 2);

	vector_pop_back(v, &rval);
	len = vector_size(v);

	ASSERT_EXPR(rval == 9);
	ASSERT_EXPR(len == 1);

	iterator_t it, it2, it3, it4;

	it = it_alloc();
	it2 = it_alloc();
	it3 = it_alloc();
	it4 = it_alloc();

	vector_begin(v, it);

	printf("%d\n", c_deref_data(int, c_it_data(it)));

	c_it_move(it);

	printf("%d\n", c_deref_data(int, c_it_data(it)));

	vector_begin(v, it2);

	printf("%d\n\n", c_deref_data(int, c_it_data(it)));

	for (vector_begin(v, it3), vector_end(v, it4); c_it_cmp(it3, it4);
	     c_it_move(it3))
		printf("%d\n", c_deref_data(int, c_it_data(it3)));

	for (vector_begin(v, it3), vector_end(v, it4); c_it_cmp(it3, it4);
	     c_it_move(it3))
		printf("%d\n", c_deref_data(int, c_it_data(it3)));

	it_free(it);
	it_free(it2);
	it_free(it3);
	it_free(it4);

	vector_free(v);
}

void test_vector_erase(void)
{
	INIT_TEST_ASSERT();

	vector_t v = vector_alloc_empty(int, NULL);

	ASSERT_NOT_NULL(v);

	size_t len;

	vector_push_back(v, c_data_int32(-5), C_DATA_TYPE_INT);
	vector_push_back(v, c_data_int32(6), C_DATA_TYPE_INT);
	vector_push_back(v, c_data_int32(3), C_DATA_TYPE_INT);
	vector_push_back(v, c_data_int32(-1), C_DATA_TYPE_INT);
	vector_push_back(v, c_data_int32(7), C_DATA_TYPE_INT);
	vector_push_back(v, c_data_int32(3), C_DATA_TYPE_INT);
	vector_push_back(v, c_data_int32(8), C_DATA_TYPE_INT);
	len = vector_size(v);

	ASSERT_EXPR(len == 7);

	iterator_t it, it2, it3, it4;

	it = it_alloc();
	it2 = it_alloc();
	it3 = it_alloc();
	it4 = it_alloc();

	vector_begin(v, it);

	printf("%d\n", c_deref_data(int, c_it_data(it)));

	printf("%d\n", c_deref_data(int, c_it_data(it)));

	vector_begin(v, it2);
	c_it_move(it2);

	printf("%d\n\n", c_deref_data(int, c_it_data(it)));

	for (vector_begin(v, it3), vector_end(v, it4); c_it_cmp(it3, it4);
	     c_it_move(it3))
		printf("%d\n", c_deref_data(int, c_it_data(it3)));

	for (vector_begin(v, it3), vector_end(v, it4); c_it_cmp(it3, it4);
	     c_it_move(it3))
		printf("%d\n", c_deref_data(int, c_it_data(it3)));

	vector_begin(v, it);
	// c_it_advance(it, 2);

	vector_begin(v, it2);
	c_it_advance(it2, 5);

	vector_erase(v, it, it2);

	for (vector_begin(v, it3), vector_end(v, it4); c_it_cmp(it3, it4);
	     c_it_move(it3))
		printf("%d\n", c_deref_data(int, c_it_data(it3)));

	it_free(it);
	it_free(it2);
	it_free(it3);
	it_free(it4);

	vector_free(v);
}

int main(void)
{
	test_vector_push_back();
	test_vector_pop_back();
	test_vector_erase();

	return 0;
}
