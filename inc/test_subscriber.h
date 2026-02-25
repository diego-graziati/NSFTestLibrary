#ifndef __TEST_SUBSCRIBER_H__
#define __TEST_SUBSCRIBER_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mytest_test_category mytest_test_category;
typedef struct mytest_test_unit mytest_test_unit;

/**
 * @author Diego Graziati
 * @brief This function initializes a single test category and all its sub components to their default values.
 */
void mytest_init_test_category (mytest_test_category** test_category);
/**
 * @author Diego Graziati
 * @brief This function adds a test unit to the array of test units of a single test category.
 */
void mytest_subscribe_test_unit (mytest_test_category* test_category, mytest_test_unit* test_unit);
/**
 * @author Diego Graziati
 * @brief This function executes all test units inside a single test category, in the order they were added before the execution.
 */
void mytest_execute_category_tests (mytest_test_category* test_category);
/**
 * @author Diego Graziati
 * @brief This function frees all memory occupied by a single test category.
 */
void mytest_destroy_test_category (mytest_test_category* test_category);
/**
 * @author Diego Graziati
 * @brief This function handles all memory related matters when writing a report, returning it directly to you.
 */
mytest_report_type mytest_write_report (const char* message,  size_t message_length, int status);

#ifdef __cplusplus
}
#endif

#endif