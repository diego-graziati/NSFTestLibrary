#ifndef __TEST_UNIT_TYPE_H__
#define __TEST_UNIT_TYPE_H__

#include <types/test_report_type.h>
#include <miscellaneous/test_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup mytest_types
 * @{
 */
/**
 * @author Diego Graziati
 * @brief This structure represents a single testing unit.
 * @warning Do not initialize this data structure by hand. See the "See also" section to learn what to use to properly initialize the data structure.
 * @see mytest_init_test_unit to initialize this data structure.
 * @see mytest_submit_test_to_test_unit to link a test function to the test unit.
 */
typedef struct mytest_test_unit
{
    /**
     * @author Diego Graziati
     * @brief This parameter is the name of the test unit. It isn't necessarily unique.
     */
    const char test_name[MYTEST_TEST_UNIT_MAX_NAME_LENGTH + 1];
    /**
     * @author Diego Graziati
     * @brief This parameter is the test unit actual test function.
     * @see mytest_submit_test_to_test_unit to link a test function to the test unit.
     */
    void (*test_callback_fn)(mytest_report_type_t* test_report, uint32_t test_unit_index);
}
mytest_test_unit;

/** }@ */

/**
 * @typedef
 * @author Diego Graziati
 */
typedef mytest_test_unit* mytest_test_unit_t;

#ifdef __cplusplus
}
#endif

#endif
