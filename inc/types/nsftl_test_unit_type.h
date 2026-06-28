#ifndef __NSFTL_TEST_UNIT_TYPE_H__
#define __NSFTL_TEST_UNIT_TYPE_H__

#include <types/nsftl_test_report_type.h>
#include <miscellaneous/nsftl_test_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup nsftl_types
 * @{
 */
/**
 * @details
 * A test unit is intended as a completely independent unit of testing, 'thus implying that one failing shouldn't impede the execution of the next test unit.
 * What test a test unit must run is decided entirely by the programmer via the test_callback_fn, often referred to as test unit's test function, since it
 * contains the actual test's code.
 * A test unit's execution must always produce a test report.
 * 
 * @author Diego Graziati
 * 
 * @brief This structure represents a single testing unit.
 * 
 * @warning Do not initialize this data structure by hand. See the "See also" section to learn what to use to properly initialize the data structure.
 * 
 * @see nsftl_init_test_unit to initialize this data structure.
 * @see nsftl_submit_test_to_test_unit to link a test function to the test unit.
 */
struct nsftl_test_unit
{
    /**
     * @author Diego Graziati
     * 
     * @brief This parameter is the name of the test unit. It isn't necessarily unique.
     * 
     * @note The test_name length is fixed at NSFTL_TEST_UNIT_MAX_NAME_LENGTH writable characters plus one index left for the \0.
     */
    const char test_name[NSFTL_TEST_UNIT_MAX_NAME_LENGTH + 1];
    /**
     * @author Diego Graziati
     * 
     * @brief This parameter is the test unit actual test function.
     * 
     * @see nsftl_submit_test_to_test_unit to link a test function to the test unit.
     */
    void (*test_callback_fn)(nsftl_test_report_t* test_report, nsftl_index_t test_unit_index);
};

/**
 * @typedef
 * @author Diego Graziati
 */
typedef struct nsftl_test_unit nsftl_test_unit;
/** }@ */

/**
 * @typedef
 * @author Diego Graziati
 */
typedef nsftl_test_unit* nsftl_test_unit_t;

#ifdef __cplusplus
}
#endif

#endif
