#ifndef __TEST_UTILS_H__
#define __TEST_UTILS_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @author Diego Graziati
 * @brief This function handles all memory related matters when writing a report, returning it directly to you.
 * @param report it is the report you want to write. It should only be passed as NULL, or otherwise you'll experience memory leakeage.
 * @param message it is the sentence that needs to be written inside the report.
 * @param message_length it is the report's message length. It must not be bigger than or equal to MYTEST_TEST_REPORT_MAX_MESSAGE_LENGTH.
 * @param status the test return status after its execution.
 * @returns MYTEST_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT, MYTEST_REPORT_MESSAGE_IS_TOO_LONG, MYTEST_SUCCESS
 */
uint32_t mytest_write_report (mytest_report_type_t* report, const char* message,  size_t message_length, uint32_t status);

/**
 * @author Diego Graziati
 * @brief This function handles the test function callback assignment to the test unit passed as argument.
 * @param test_unit this is the test unit target. At the end it will have a test_call_fn attached to it.
 * @param test_callback_fn the test function defined by the user.
 * @returns MYTEST_UNABLE_TO_SUBMIT_TEST_FUNCTION_TO_TEST_UNIT, MYTEST_SUCCESS
 */
uint32_t mytest_submit_test_to_test_unit (mytest_test_unit_t test_unit, void (*test_callback_fn)(mytest_report_type_t* test_report, uint32_t index));

#ifdef __cplusplus
}
#endif

#endif