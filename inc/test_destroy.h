#ifndef __TEST_DESTROY_H__
#define __TEST_DESTROY_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mytest_test_category* mytest_test_category_t;
typedef struct mytest_report_type* mytest_report_type_t;

/**
 * @author Diego Graziati
 * @brief This function frees all memory occupied by a single test category.
 */
void mytest_destroy_test_category (mytest_test_category_t* test_category);

void mytest_destroy_test_unit (mytest_test_unit_t* test_unit);

void mytest_destroy_test_report (mytest_report_type_t* test_report);

#ifdef __cplusplus
}
#endif

#endif