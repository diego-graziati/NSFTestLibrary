#ifndef __NSFTL_TEST_CATEGORY_H__
#define __NSFTL_TEST_CATEGORY_H__

#include <types/nsftl_test_unit_type.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup nsftl_types
 * @{
 */
/**
 * @details
 * A test category is intended as a container of test units, loosely connected and completely independent. Every single unit inside a category is indipendent from
 * the others. What links every unit inside a category is only the logical concept level.
 * 
 * @author Diego Graziati
 * 
 * @brief A test category is a collection of test units with their corresponding test reports once executed.
 * 
 * @warning Do not initialize the data structure by hand. Instead, use the appropriate library's functions.
 * 
 * @see nsftl_init_test_category to initialize a test category.
 * @see nsftl_destroy_test_category to destroy a test category (and all its test units and test reports).
 * @see nsftl_subscribe_test_unit to subscribe a test unit to a test category.
 * @see nsftl_execute_category_test to execute a specified test unit inside a test category.
 */
struct nsftl_test_category 
{
    /**
     * @author Diego Graziati
     * 
     * @brief This is the test category's name. It is decided during the initialization by the programmer.
     * 
     * @note It can be long at most NSFTL_TEST_CATEGORY_MAX_NAME_LENGTH characters.
     */
    const char category_name[NSFTL_TEST_CATEGORY_MAX_NAME_LENGTH + 1];
    /**
     * @author Diego Graziati
     * 
     * @brief This is the test units' array.
     * 
     * @note Its capacity and size are always identical to the test reports' array's capacity and size.
     */
    nsftl_test_unit_t tests;
    /**
     * @author Diego Graziati
     * 
     * @brief This is the test reports' array.
     * 
     * @note Its capacity and size are always identical to the test units' array's capacity and size.
     */
    nsftl_test_report_t reports;
    /**
     * @author Diego Graziati
     * 
     * @brief This is the test units' and test reports' arrays' dimensions.
     */
    uint32_t capacity;
    /**
     * @author Diego Graziati
     * 
     * @brief This is the test units' and test reports' arrays actual used indexes, meaning their actual occupied space.
     * 
     * @note size <= capacity always.
     */
    uint32_t size;
};

/**
 * @typedef
 * @author Diego Graziati
 */
typedef struct nsftl_test_category nsftl_test_category;
/** }@ */
/**
 * @typedef
 * @author Diego Graziati
 */
typedef nsftl_test_category* nsftl_test_category_t;


#ifdef __cplusplus
}
#endif

#endif