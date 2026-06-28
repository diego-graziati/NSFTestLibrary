#ifndef __NSFTL_TEST_REPORT_TYPE_H__
#define __NSFTL_TEST_REPORT_TYPE_H__

#include <types/nsftl_base_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup nsftl_types
 * @{
 */
/**
 * @details
 * A report is intended as a description, both informative and analytical of the test's results and performance.
 * It's the bridge between the test unit's test function and the outside world, enabling eventual frameworks to collect the data inside the reports of
 * all test units inside a test category as a way to analyze the test category's performance.
 * The data inside a test report must always be decided by the programmer who is writing the test unit's test function.
 * A test report exists only as a product of the paired test unit's execution.
 * 
 * @author Diego Graziati
 * 
 * @brief This structure represents a single report, containing all useful infos regarding the test execution.
 * 
 * @warning Do not initialize this data structure by hand. Instead use the appropriate function provided by the library
 * 
 * @see nsftl_write_report to initialize a report.
 * @see nsftl_destroy_test_report to destroy a report.
 */
struct nsftl_test_report 
{
    /**
     * @author Diego Graziati
     * 
     * @brief This should be a short, only informative message detailing the test's return status. It must be written by the programmer inside the test unit's function.
     * 
     * @note Its length isn't fixed. However, it can be long at most NSFTL_TEST_REPORT_MAX_MESSAGE_LENGTH characters.
     * 
     * @see NSFTL_TEST_REPORT_MAX_MESSAGE_LENGTH
     */
    const char* message;
    /**
     * @author Diego Graziati
     * 
     * @brief This parameter is used by the programmer writing the test unit's function as a way to communicate to the outside what happened inside the function once it stopped.
     * 
     * @note We suggest the use of constants (in the form you prefer) with the same type as the status.
     */
    nsftl_status_t status;
    nsftl_time_t start_time;
    nsftl_time_t end_time;
};

/**
 * @typedef
 * @author Diego Graziati
 */
typedef struct nsftl_test_report nsftl_test_report;
/**}@ */
/**
 * @typedef
 * @author Diego Graziati
 */
typedef nsftl_test_report* nsftl_test_report_t;

#ifdef __cplusplus
}
#endif

#endif