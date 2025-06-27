#include "../vector.h"
#include "../common.h"
#include "test.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <glib.h>

typedef struct {
	vector_t v;
} TestFixture;

static void test_vector_setup(TestFixture *fixture, gconstpointer data)
{
	fixture->v = vector_alloc_empty(int, NULL);
	g_assert_nonnull(fixture->v);
}

static void test_vector_teardown(TestFixture *fixture, gconstpointer data)
{
	vector_free(fixture->v);
	fixture->v = NULL;
}

void add_values()
{
}

static void test_vector_push_back(TestFixture *fixture, gconstpointer data)
{
	vector_t v = fixture->v;
	int arr[] = { -5, 6, 3, -1, 7, 3, 8 };
	size_t arr_size = sizeof(arr) / sizeof(*arr);
	int i;
	void *p = c_data_int32(4);

	printf("PTR: %d\n", 1);
	printf("PTR: %d\n", *(int *)p);

	vector_push_back_m(v, c_data_int32(-5), int);
	g_assert_cmpint(vector_size(v), ==, 1);

	printf("PTR: %d\n", *(int *)p);

	vector_push_back_m(v, c_data_int32(6), int);
	g_assert_cmpint(vector_size(v), ==, 2);

	vector_push_back_m(v, c_data_int32(3), int);
	g_assert_cmpint(vector_size(v), ==, 3);

	vector_push_back_m(v, c_data_int32(-1), int);
	g_assert_cmpint(vector_size(v), ==, 4);

	vector_push_back_m(v, c_data_int32(7), int);
	g_assert_cmpint(vector_size(v), ==, 5);

	vector_push_back_m(v, c_data_int32(3), int);
	g_assert_cmpint(vector_size(v), ==, 6);

	vector_push_back_m(v, c_data_int32(8), int);
	g_assert_cmpint(vector_size(v), ==, 7);

	iterator_t it, it2, it3, it4, it5;

	it = it_alloc();
	it2 = it_alloc();
	it3 = it_alloc();
	it4 = it_alloc();
	it5 = it_alloc();

	vector_begin(v, it);
	g_assert_cmpint(c_deref_data(int, c_it_data(it)), ==, -5);

	c_it_move(it);
	g_assert_cmpint(c_deref_data(int, c_it_data(it)), ==, 6);

	vector_begin(v, it2);
	g_assert_cmpint(c_deref_data(int, c_it_data(it)), ==, 6);

	for (i = 0, vector_begin(v, it3), vector_end(v, it4);
	     c_it_cmp(it3, it4); c_it_move(it3), ++i)
		g_assert_cmpint(c_deref_data(int, c_it_data(it3)), ==, arr[i]);

	for (i = 0, vector_begin(v, it3), vector_end(v, it4); i < arr_size;
	     c_it_move(it3), ++i)
		g_assert_cmpint(c_deref_data(int, c_it_data(it3)), ==, arr[i]);

	vector_end(v, it5);
	g_assert_cmpint(c_deref_data(int, c_it_data(it5)), ==, 8);

	it_free(it);
	it_free(it2);
	it_free(it3);
	it_free(it4);
	it_free(it5);
}

static void test_vector_pop_back(TestFixture *fixture, gconstpointer data)
{
	vector_t v = fixture->v;
	int arr[] = { 3 };
	size_t arr_size = sizeof(arr) / sizeof(*arr);
	int rval;
	int i;

	vector_push_back_m(v, c_data_int32(-5), int);
	g_assert_cmpint(vector_size(v), ==, 1);

	vector_push_back_m(v, c_data_int32(6), int);
	g_assert_cmpint(vector_size(v), ==, 2);

	vector_pop_back(v, NULL);
	g_assert_cmpint(vector_size(v), ==, 1);

	vector_pop_back(v, NULL);
	g_assert_cmpint(vector_size(v), ==, 0);

	vector_pop_back(v, NULL);
	g_assert_cmpint(vector_size(v), ==, 0);

	vector_push_back_m(v, c_data_int32(3), int);
	g_assert_cmpint(vector_size(v), ==, 1);

	vector_push_back_m(v, c_data_int32(7), int);
	g_assert_cmpint(vector_size(v), ==, 2);

	vector_push_back_m(v, c_data_int32(8), int);
	g_assert_cmpint(vector_size(v), ==, 3);

	vector_pop_back(v, &rval);
	g_assert_cmpint(vector_size(v), ==, 2);
	g_assert_cmpint(rval, ==, 8);

	vector_pop_back(v, NULL);
	g_assert_cmpint(vector_size(v), ==, 1);

	vector_push_back_m(v, c_data_int32(9), int);
	g_assert_cmpint(vector_size(v), ==, 2);

	vector_pop_back(v, &rval);
	g_assert_cmpint(vector_size(v), ==, 1);
	g_assert_cmpint(rval, ==, 9);

	iterator_t it, it2, it3, it4, it5;

	it = it_alloc();
	it2 = it_alloc();
	it3 = it_alloc();
	it4 = it_alloc();
	it5 = it_alloc();

	vector_begin(v, it);
	g_assert_cmpint(c_deref_data(int, c_it_data(it)), ==, 3);

	c_it_move(it);
	g_assert_cmpint(c_deref_data(int, c_it_data(it)), ==, 3);

	c_it_move(it);
	g_assert_cmpint(c_deref_data(int, c_it_data(it)), ==, 3);

	vector_begin(v, it2);
	g_assert_cmpint(c_deref_data(int, c_it_data(it)), ==, 3);

	for (i = 0, vector_begin(v, it3), vector_end(v, it4);
	     c_it_cmp(it3, it4); c_it_move(it3), ++i)
		g_assert_cmpint(c_deref_data(int, c_it_data(it3)), ==, arr[i]);

	for (i = 0, vector_begin(v, it3), vector_end(v, it4); i < arr_size;
	     c_it_move(it3), ++i)
		g_assert_cmpint(c_deref_data(int, c_it_data(it3)), ==, arr[i]);

	vector_end(v, it5);
	g_assert_cmpint(c_deref_data(int, c_it_data(it5)), ==, 3);

	it_free(it);
	it_free(it2);
	it_free(it3);
	it_free(it4);
	it_free(it5);
}

static void test_vector_erase(TestFixture *fixture, gconstpointer data)
{
	vector_t v = fixture->v;
	int arr[] = { -5, 6, 3, -1, 7, 3, 8 };
	size_t arr_size = sizeof(arr) / sizeof(*arr);
	int arr_new[] = { -5, 6, 8 };
	int i;

	vector_push_back_m(v, c_data_int32(-5), int);
	vector_push_back_m(v, c_data_int32(6), int);
	vector_push_back_m(v, c_data_int32(3), int);
	vector_push_back_m(v, c_data_int32(-1), int);
	vector_push_back_m(v, c_data_int32(7), int);
	vector_push_back_m(v, c_data_int32(3), int);
	vector_push_back_m(v, c_data_int32(8), int);

	g_assert_cmpint(vector_size(v), ==, 7);

	iterator_t it, it2, it3, it4, it5;

	it = it_alloc();
	it2 = it_alloc();
	it3 = it_alloc();
	it4 = it_alloc();
	it5 = it_alloc();

	vector_begin(v, it);
	g_assert_cmpint(c_deref_data(int, c_it_data(it)), ==, -5);

	vector_begin(v, it2);
	c_it_move(it2);

	g_assert_cmpint(c_deref_data(int, c_it_data(it2)), ==, 6);

	for (i = 0, vector_begin(v, it3), vector_end(v, it4);
	     c_it_cmp(it3, it4); c_it_move(it3), ++i)
		g_assert_cmpint(c_deref_data(int, c_it_data(it3)), ==, arr[i]);

	for (i = 0, vector_begin(v, it3), vector_end(v, it4); i < arr_size;
	     c_it_move(it3), ++i)
		g_assert_cmpint(c_deref_data(int, c_it_data(it3)), ==, arr[i]);

	vector_begin(v, it);
	c_it_advance(it, 2);

	vector_begin(v, it2);
	c_it_advance(it2, 5);

	vector_erase(v, it, it2);

	for (i = 0, vector_begin(v, it3), vector_end(v, it4);
	     c_it_cmp(it3, it4); c_it_move(it3), ++i)
		g_assert_cmpint(c_deref_data(int, c_it_data(it3)), ==,
				arr_new[i]);

	vector_end(v, it5);
	g_assert_cmpint(c_deref_data(int, c_it_data(it5)), ==, 8);

	it_free(it);
	it_free(it2);
	it_free(it3);
	it_free(it4);
	it_free(it5);
}

static void test_vector_erase_at(TestFixture *fixture, gconstpointer data)
{
	vector_t v = fixture->v;
	int arr1[] = { -5, 6, 3, -1, 7, 3, 8 };
	int arr2[] = { -5, 6, -1, 7, 3, 8 };
	int arr3[] = { -5, 6, 7 };
	int arr4[] = { 6, 7 };
	int i;

	vector_push_back_m(v, c_data_int32(-5), int);
	vector_push_back_m(v, c_data_int32(6), int);
	vector_push_back_m(v, c_data_int32(3), int);
	vector_push_back_m(v, c_data_int32(-1), int);
	vector_push_back_m(v, c_data_int32(7), int);
	vector_push_back_m(v, c_data_int32(3), int);
	vector_push_back_m(v, c_data_int32(8), int);

	iterator_t it, it2;

	it = it_alloc();
	it2 = it_alloc();

	for (i = 0, vector_begin(v, it), vector_end(v, it2); c_it_cmp(it, it2);
	     c_it_move(it), ++i)
		g_assert_cmpint(c_deref_data(int, c_it_data(it)), ==, arr1[i]);

	vector_begin(v, it);
	c_it_advance(it, 2);

	vector_erase_at(v, it);

	for (i = 0, vector_begin(v, it), vector_end(v, it2); c_it_cmp(it, it2);
	     c_it_move(it), ++i)
		g_assert_cmpint(c_deref_data(int, c_it_data(it)), ==, arr2[i]);

	vector_begin(v, it);
	c_it_advance(it, 2);

	vector_erase_at(v, it);

	c_it_advance(it, 1);

	vector_erase_at(v, it);
	vector_erase_at(v, it);

	for (i = 0, vector_begin(v, it), vector_end(v, it2); c_it_cmp(it, it2);
	     c_it_move(it), ++i)
		g_assert_cmpint(c_deref_data(int, c_it_data(it)), ==, arr3[i]);

	vector_begin(v, it);
	vector_erase_at(v, it);

	for (i = 0, vector_begin(v, it), vector_end(v, it2); c_it_cmp(it, it2);
	     c_it_move(it), ++i)
		g_assert_cmpint(c_deref_data(int, c_it_data(it)), ==, arr4[i]);

	it_free(it);
	it_free(it2);
}

static void test_vector_clear(TestFixture *fixture, gconstpointer data)
{
	vector_t v = fixture->v;
	int arr1[] = { -5, 6, 3, -1, 7, 3, 8 };
	size_t arr1_size = sizeof(arr1) / sizeof(*arr1);
	int arr2[] = {};
	size_t arr2_size = sizeof(arr2) / sizeof(*arr2);
	int i;

	vector_push_back_m(v, c_data_int32(-5), int);
	vector_push_back_m(v, c_data_int32(6), int);
	vector_push_back_m(v, c_data_int32(3), int);
	vector_push_back_m(v, c_data_int32(-1), int);
	vector_push_back_m(v, c_data_int32(7), int);
	vector_push_back_m(v, c_data_int32(3), int);
	vector_push_back_m(v, c_data_int32(8), int);

	iterator_t it, it2;

	it = it_alloc();
	it2 = it_alloc();

	for (i = 0, vector_begin(v, it), vector_end(v, it2); c_it_cmp(it, it2);
	     c_it_move(it), ++i)
		g_assert_cmpint(c_deref_data(int, c_it_data(it)), ==, arr1[i]);

	g_assert_cmpint(vector_size(v), ==, arr1_size);

	vector_clear(v);

	vector_begin(v, it);

	for (i = 0, vector_begin(v, it), vector_end(v, it2); c_it_cmp(it, it2);
	     c_it_move(it), ++i)
		g_assert_cmpint(c_deref_data(int, c_it_data(it)), ==, arr2[i]);

	g_assert_cmpint(vector_size(v), ==, arr2_size);

	it_free(it);
	it_free(it2);
}

int main(int argc, char **argv)
{
	int result;

	g_test_init(&argc, &argv, NULL);

	// set_mapeditor_directory("G_TEST_SRCDIR", "src/test/medir");

	ADD_TEST(vector, push_back, TestFixture, NULL);
	ADD_TEST(vector, pop_back, TestFixture, NULL);
	ADD_TEST(vector, erase, TestFixture, NULL);
	ADD_TEST(vector, erase_at, TestFixture, NULL);
	ADD_TEST(vector, clear, TestFixture, NULL);

	/* Run the tests */
	result = g_test_run();

	/* Don't write files to the source dir */
	// set_mapeditor_directory("G_TEST_BUILDDIR", "src/test/medir-output");

	return result;
}
