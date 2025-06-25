#ifndef __C_TEMPLATE_LIB_TEST_INCLUDED_H__
#define __C_TEMPLATE_LIB_TEST_INCLUDED_H__

#define ADD_TEST(entity, function, fixture, tdata)                    \
	g_test_add("/" #entity "/" #function, TestFixture, tdata,     \
		   test_##entity##_setup, test_##entity##_##function, \
		   test_##entity##_teardown);

void test_list(void);
void test_stack(void);
void test_queue(void);
void test_vector(void);
void test_pair(void);

#endif // __C_TEMPLATE_LIB_TEST_INCLUDED_H__
