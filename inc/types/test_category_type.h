#ifndef __TEST_CATEGORY_H__
#define __TEST_CATEGORY_H__

#include <types/test_unit_type.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mytest_test_category 
{
    const char category_name[MYTEST_TEST_CATEGORY_MAX_NAME_LENGTH + 1];
    mytest_test_unit_t tests;
    mytest_report_type_t reports;
    uint32_t capacity;
    uint32_t size;
}
mytest_test_category;

typedef mytest_test_category* mytest_test_category_t;

#ifdef __cplusplus
}
#endif

#endif