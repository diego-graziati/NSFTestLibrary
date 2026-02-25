#ifndef __TEST_CATEGORY_H__
#define __TEST_CATEGORY_H__

#include <types/test_unit_type.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mytest_test_category 
{
    mytest_test_unit* tests;
    mytest_report_type* reports;
    uint32_t capacity;
    uint32_t size;
}
mytest_test_category;

#ifdef __cplusplus
}
#endif

#endif