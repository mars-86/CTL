#ifndef __C_TEST_ASSERT_INCLUDED_H__
#define __C_TEST_ASSERT_INCLUDED_H__

#include <stdio.h>
#include <stdlib.h>

#define __COLOR_DEFAULT "\x1B[0m"
#define __COLOR_SUCCESS "\x1B[32m" // GREEN
#define __COLOR_FAIL "\x1B[31m" // RED

#define __ASSERT_SUCCESS "SUCCESS"
#define __ASSERT_FAIL "FAIL"

#define __TEST_CNTR \
    int __tcntr = 0
#define __SUCCESS_CNTR \
    int __scntr = 0
#define __FAIL_CNTR \
    int __fcntr = 0

#define __INC_TEST_CNTR \
    __tcntr++
#define __INC_SUCCESS_CNTR \
    __scntr++
#define __INC_FAIL_CNTR \
    __fcntr++

#define __PRINT_MSG(msg, stream, color, status) \
    fprintf(stream, color "%s" __COLOR_DEFAULT ": %s:%d assertion [" msg "]\n", status, __FILE__, __LINE__);

#define __ASSERT(expr)                                                     \
    do {                                                                   \
        __INC_TEST_CNTR;                                                   \
        if (!(expr)) {                                                     \
            __PRINT_MSG(#expr, stdout, __COLOR_FAIL, __ASSERT_FAIL);       \
            __INC_FAIL_CNTR;                                               \
        } else {                                                           \
            __PRINT_MSG(#expr, stdout, __COLOR_SUCCESS, __ASSERT_SUCCESS); \
            __INC_SUCCESS_CNTR;                                            \
        }                                                                  \
    } while (0)

#define INIT_TEST_ASSERT() \
    __TEST_CNTR;           \
    __SUCCESS_CNTR;        \
    __FAIL_CNTR;

#define ASSERT_NOT_NULL(expr) \
    __ASSERT((expr) != NULL)

#define ASSERT_NULL(expr) \
    __ASSERT((expr) == NULL)

#define ASSERT_EXPR(expr) \
    __ASSERT(expr)

#define ASSERT_IS_CHAR(val) \
    __ASSERT(val == sizeof(char))

#define ASSERT_IS_SHORT(val) \
    __ASSERT(val == sizeof(short))

#define ASSERT_IS_INT(val) \
    __ASSERT(val == sizeof(int))

#define ASSERT_IS_LONG(val) \
    __ASSERT(val == sizeof(long))

#define ASSERT_IS_UCHAR(val) \
    __ASSERT((val == sizeof(char)) && (val >= 0))

#define ASSERT_IS_USHORT(val) \
    __ASSERT((val == sizeof(short)) && (val >= 0))

#define ASSERT_IS_UINT(val) \
    __ASSERT((val == sizeof(int)) && (val >= 0))

#define ASSERT_IS_ULONG(val) \
    __ASSERT((val == sizeof(long)) && (val >= 0))

#endif // __C_TEST_ASSERT_INCLUDED_H__
