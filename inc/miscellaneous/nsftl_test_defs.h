#ifndef __NSFTL_TEST_DEFS_H__
#define __NSFTL_TEST_DEFS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    NSFTL_DEFAULT_TESTS_ARRAY_SIZE = 10U,
    TEST_REPORT_NOT_INITIALIZED = 1,
    NSFTL_TEST_UNIT_MAX_NAME_LENGTH = 256U,
    NSFTL_TEST_CATEGORY_MAX_NAME_LENGTH = NSFTL_TEST_UNIT_MAX_NAME_LENGTH,
    NSFTL_TEST_REPORT_MAX_MESSAGE_LENGTH = 4096U
};

#ifdef __cplusplus
}
#endif

#endif