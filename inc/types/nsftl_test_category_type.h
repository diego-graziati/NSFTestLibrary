#ifndef __NSFTL_TEST_CATEGORY_H__
#define __NSFTL_TEST_CATEGORY_H__

#include <types/nsftl_test_unit_type.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nsftl_test_category 
{
    const char category_name[NSFTL_TEST_CATEGORY_MAX_NAME_LENGTH + 1];
    nsftl_test_unit_t tests;
    nsftl_report_type_t reports;
    uint32_t capacity;
    uint32_t size;
}
nsftl_test_category;

typedef nsftl_test_category* nsftl_test_category_t;

#ifdef __cplusplus
}
#endif

#endif