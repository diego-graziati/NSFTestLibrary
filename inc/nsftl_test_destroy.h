#ifndef __NSFTL_TEST_DESTROY_H__
#define __NSFTL_TEST_DESTROY_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nsftl_test_category* nsftl_test_category_t;
typedef struct nsftl_report_type* nsftl_report_type_t;

/**
 * @author Diego Graziati
 * @brief This function frees all memory occupied by a single test category.
 */
void mynsftl_test_destroy_test_category (nsftl_test_category_t* test_category);

void mynsftl_test_destroy_test_unit (nsftl_test_unit_t* test_unit);

void mynsftl_test_destroy_test_report (nsftl_report_type_t* test_report);

#ifdef __cplusplus
}
#endif

#endif