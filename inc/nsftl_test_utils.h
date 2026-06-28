#ifndef __NSFT_TEST_UTILS_H__
#define __NSFT_TEST_UTILS_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 
 * 
 * @param report 
 * @param start_time
 * @return nsftl_status_t 
 */
nsftl_status_t nsftl_start_report_timer (nsftl_test_report_t report);

/**
 * @brief 
 * 
 * @param report 
 * @param end_time 
 * @return nsftl_status_t 
 */
nsftl_status_t nsftl_stop_report_timer (nsftl_test_report_t report);

/**
 * @author Diego Graziati
 * 
 * @brief This function handles all memory related matters when writing a report, returning it directly to you.
 * 
 * @param[out] report It is the report you want to write. It should only be passed as NULL, or otherwise you'll experience memory leakeage.
 * @param[in] message It is the sentence that needs to be written inside the report.
 * @param[in] message_length It is the report's message length. It must not be bigger than or equal to MYTEST_TEST_REPORT_MAX_MESSAGE_LENGTH.
 * @param[in] status The test return status after its execution.
 * 
 * @retval NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT If the function fails to allocate memory at any point.
 * @retval NSFTL_REPORT_MESSAGE_IS_TOO_LONG If the passed message is longer than NSFTL_TEST_REPORT_MAX_MESSAGE_LENGTH characters.
 * @retval NSFTL_SUCCESS Everything went right.
 */
nsftl_status_t nsftl_write_report (nsftl_test_report_t* report, const char* message,  size_t message_length, nsftl_status_t status);

/**
 * @author Diego Graziati
 * 
 * @brief This function handles the test function callback assignment to the test unit passed as argument.
 * 
 * @param[in] test_unit This is the test unit target. At the end it will have a test_call_fn attached to it.
 * @param[in] test_callback_fn The test function defined by the user.
 * 
 * @retval NSFTL_UNABLE_TO_SUBMIT_TEST_FUNCTION_TO_TEST_UNIT If the function fails to link the test_callback_fn to the test_unit.
 * @retval NSFTL_SUCCESS Everything went right.
 */
nsftl_status_t nsftl_submit_test_to_test_unit (nsftl_test_unit_t test_unit, void (*test_callback_fn)(nsftl_test_report_t* test_report, nsftl_index_t index));

#ifdef __cplusplus
}
#endif

#endif