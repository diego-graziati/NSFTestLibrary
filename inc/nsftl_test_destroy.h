#ifndef __NSFTL_TEST_DESTROY_H__
#define __NSFTL_TEST_DESTROY_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nsftl_test_category* nsftl_test_category_t;
typedef struct nsftl_test_report* nsftl_test_report_t;

/**
 * @addtogroup nsftl_core
 * @{
 */
/**
 * @author Diego Graziati
 * 
 * @brief This function frees all memory occupied by a single test category.
 * 
 * @warning If you want to reuse the test category you must first reinitialize it.
 * 
 * @param [out] test_category It is the test category that needs to be freed.
 * 
 * @returns Nothing
 */
void nsftl_destroy_test_category (nsftl_test_category_t* test_category);

/**
 * @author Diego Graziati
 * 
 * @brief This function frees all memory occupied by a single test unit.
 * 
 * @warning If you want to reuse the test unit you must first reinitialize it.
 *  
 * @param [out] test_unit It is the test unit that needs to be freed.
 * 
 * @returns Nothing
 */
void nsftl_destroy_test_unit (nsftl_test_unit_t* test_unit);

/**
 * @author Diego Graziati
 * 
 * @brief This function frees all memory occupied by a single test report.
 * 
 * @warning If you want to reuse the test report you must first reinitialize it.
 * 
 * @param [out] test_report It is the test report that needs to be freed.
 * 
 * @returns Nothing
 */
void nsftl_destroy_test_report (nsftl_test_report_t* test_report);

/**}@ */

#ifdef __cplusplus
}
#endif

#endif