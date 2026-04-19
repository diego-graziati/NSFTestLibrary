#ifndef __TEST_EXECUTE_H__
#define __TEST_EXECUTE_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mytest_test_category* mytest_test_category_t;

uint32_t mytest_execute_category_test (mytest_test_category_t test_category, uint32_t index);

#ifdef __cplusplus
}
#endif

#endif