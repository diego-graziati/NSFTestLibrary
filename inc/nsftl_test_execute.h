#ifndef __NSFTL_TEST_EXECUTE_H__
#define __NSFTL_TEST_EXECUTE_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nsftl_test_category* nsftl_test_category_t;

uint32_t mynsftl_test_execute_category_test (nsftl_test_category_t test_category, uint32_t index);

#ifdef __cplusplus
}
#endif

#endif