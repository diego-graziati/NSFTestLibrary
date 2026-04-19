#ifndef __NSFTL_TEST_INIT_H__
#define __NSFTL_TEST_INIT_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nsftl_test_category* nsftl_test_category_t;
typedef struct nsftl_test_unit* nsftl_test_unit_t;


/**
 * @addtogroup mytest_core
 * @{
 */

/**
 * @author Diego Graziati
 * @brief This function initializes a single test category and all its sub components to their default values.
 */
uint32_t mynsftl_test_init_test_category (nsftl_test_category_t* test_category, const char* test_category_name);

/**
 * @author Diego Graziati
 * @brief This function initializes a single test unit. However, it doesn't assign any test function to the test unit callback function.
 * @see mytest_submit_test_to_test_unit to assign a test function to the test unit callback function just initialized.
 */
uint32_t mynsftl_test_init_test_unit (nsftl_test_unit_t* test_unit, const char* test_unit_name);

/** }@ */

#ifdef __cplusplus
}
#endif

#endif