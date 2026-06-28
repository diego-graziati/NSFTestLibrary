#ifndef __NSFTL_TEST_INIT_H__
#define __NSFTL_TEST_INIT_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nsftl_test_category* nsftl_test_category_t;
typedef struct nsftl_test_unit* nsftl_test_unit_t;
typedef struct nsftl_test_report* nsftl_test_report_t;


/**
 * @addtogroup nsftl_core
 * @{
 */

/**
 * @author Diego Graziati
 * 
 * @brief This function initializes a single test category and all its sub components to their default values.
 * 
 * @warning If the test category name has more than NSFTL_TEST_CATEGORY_MAX_NAME_LENGTH characters it will be truncated!
 * @note The test category's name can have at most NSFTL_TEST_CATEGORY_MAX_NAME_LENGTH characters.
 * 
 * @param [out] test_category It is the test category that is being initialized.
 * @param [in] test_category_name It is the test category's name.
 * 
 * @retval NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT If the function fails to allocate memory at any point.
 * @retval NSFTL_SUCCESS Everything went right.
 */
nsftl_status_t nsftl_init_test_category (nsftl_test_category_t* test_category, const char* test_category_name);

/**
 * @author Diego Graziati
 * 
 * @brief This function initializes a single test unit. However, it doesn't assign any test function to the test unit callback function.
 * 
 * @warning If the test unit's name has more than NSFTL_TEST_UNIT_MAX_NAME_LENGTH characters it will be truncated!
 * @note The test unit's name can have at most NSFTL_TEST_UNIT_MAX_NAME_LENGTH characters.
 * 
 * @see nsftl_submit_test_to_test_unit to assign a test function to the test unit callback function just initialized.
 * 
 * @param [out] test_unit It is the test unit that is being initialized.
 * @param [in] test_unit_name It is the test unit's name.
 * 
 * @retval NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT If the function fails to allocate memory at any point.
 * @retval NSFTL_SUCCESS Everything went right.
 */
nsftl_status_t nsftl_init_test_unit (nsftl_test_unit_t* test_unit, const char* test_unit_name);

/**
 * @brief 
 * 
 * @param test_report 
 * @return uint32_t 
 */
nsftl_status_t nsftl_init_test_report (nsftl_test_report_t* report);

/** }@ */

#ifdef __cplusplus
}
#endif

#endif