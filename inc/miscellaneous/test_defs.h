#ifndef __TEST_DEFS_H__
#define __TEST_DEFS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    MYTEST_DEFAULT_TESTS_ARRAY_SIZE = 10U,
    TEST_REPORT_NOT_INITIALIZED = 1,
    MYTEST_TEST_UNIT_MAX_NAME_LENGTH = 256U,
    MYTEST_TEST_CATEGORY_MAX_NAME_LENGTH = MYTEST_TEST_UNIT_MAX_NAME_LENGTH,
    MYTEST_TEST_REPORT_MAX_MESSAGE_LENGTH = 4096U
};

#ifdef __cplusplus
}
#endif

#endif