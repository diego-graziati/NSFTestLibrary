#ifndef __NSFTL_TEST_EXECUTE_H__
#define __NSFTL_TEST_EXECUTE_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nsftl_test_category* nsftl_test_category_t;

/**
 * @addtogroup nsftl_core
 * @{
 */
/**
 * @author Diego Graziati
 * @brief This function executes the test unit at the index position inside the test category's test units' array.
 * 
 * @note Every time a test unit is executed a test report for that test unit is produced and stored in the test category's test reports' array at the same index
 * as the test unit.
 * @warning Every time a test unit is executed and it's not the first time the corresponding test report is destroyed and overwritten!
 * 
 * @param [in] test_category It is the test category where the test unit we want to execute is located.
 * @param [in] index It is the position inside the test category's test units' array where the test unit we want to execute is positioned.
 * 
 * @retval NSFTL_TEST_CATEGORY_NOT_INITIALIZED If the test category hasn't been initialized yet.
 * @retval NSFTL_TEST_CATEGORY_REPORT_ARRAY_NOT_INITIALIZED If the test category's test reports' array hasn't been initialized yet. This could suggest an error
 * during the original test category's initialization, or a wrong handling of the data structure, since this shouldn't happen.
 * @retval NSFTL_TEST_INDEX_BIGGER_THAN_CATEGORY_SIZE If the passed test unit's index doesn't exist since it's bigger than the number of test units.
 * @retval NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT If the function fails to allocate memory at any point.
 * @retval NSFTL_REPORT_MESSAGE_IS_TOO_LONG If the report's message generated after execution is longer than NSFTL_TEST_REPORT_MAX_MESSAGE_LENGTH characters.
 * @retval NSFTL_SUCCESS Everything went right.
 */
nsftl_status_t nsftl_execute_category_test (nsftl_test_category_t test_category, nsftl_index_t index);

/**}@ */

#ifdef __cplusplus
}
#endif

#endif