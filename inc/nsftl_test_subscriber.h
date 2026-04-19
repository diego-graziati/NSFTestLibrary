#ifndef __NSFTL_TEST_SUBSCRIBER_H__
#define __NSFTL_TEST_SUBSCRIBER_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nsftl_test_category* nsftl_test_category_t;
typedef struct nsftl_test_unit* nsftl_test_unit_t;

/**
 * @author Diego Graziati
 * @brief This function adds a test unit to the array of test units of a single test category.
 */
uint32_t mytest_subscribe_test_unit (nsftl_test_category_t test_category, nsftl_test_unit_t* test_unit);

#ifdef __cplusplus
}
#endif

#endif