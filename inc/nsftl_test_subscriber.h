#ifndef __NSFTL_TEST_SUBSCRIBER_H__
#define __NSFTL_TEST_SUBSCRIBER_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nsftl_test_category* nsftl_test_category_t;
typedef struct nsftl_test_unit* nsftl_test_unit_t;

/**
 * @addtogroup nsftl_core
 * @{
 */
/**
 * @author Diego Graziati
 * 
 * @brief This function adds a test unit to the array of test units of a single test category.
 * 
 * @param[in] test_category It is the test category onto which you want to subscribe the test unit.
 * @param[in] test_unit It is the test unit you want to subscribe to the test category.
 * 
 * @warning The test unit will be destroyed once the subscription ends successfully!
 * 
 * @retval NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT If the function fails to allocate memory at any point.
 * @retval NSFTL_SUCCESS Everything went right.
 */
nsftl_status_t nsftl_subscribe_test_unit (nsftl_test_category_t test_category, nsftl_test_unit_t* test_unit);

/**}@ */

#ifdef __cplusplus
}
#endif

#endif