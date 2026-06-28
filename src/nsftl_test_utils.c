#include <miscellaneous/nsftl_test_statuses.h>
#include <types/nsftl_test_unit_type.h>
#include <nsftl_test_utils.h>
#include <nsftl_time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

nsftl_status_t nsftl_start_report_timer (nsftl_test_report_t report)
{
    if (report == NULL)
    {
        return NSFTL_TEST_REPORT_NOT_INITIALIZED;
    }
    
    if (report->start_time == NULL)
    {
        return NSFTL_TEST_REPORT_START_TIME_NOT_INITIALIZED;
    }

    if (nsftl_getclock_time(report->start_time) != NSFTL_SUCCESS)
    {
        return NSFTL_TEST_REPORT_FAILED_TO_GET_CLOCK_TIME;
    }

    return NSFTL_SUCCESS;
}

nsftl_status_t nsftl_stop_report_timer (nsftl_test_report_t report)
{
    if (report == NULL)
    {
        return NSFTL_TEST_REPORT_NOT_INITIALIZED;
    }

    if (report->end_time == NULL)
    {
        return NSFTL_TEST_REPORT_END_TIME_NOT_INITIALIZED;
    }

    if (nsftl_getclock_time(report->end_time) != NSFTL_SUCCESS)
    {
        return NSFTL_TEST_REPORT_FAILED_TO_GET_CLOCK_TIME;
    }

    return NSFTL_SUCCESS;
}

/**
 * @brief 
 * 
 * @param report 
 * @param message 
 * @param message_length 
 * @param status 
 * @return nsftl_status_t 
 */
nsftl_status_t nsftl_write_report (nsftl_test_report_t* report, const char* message,  size_t message_length, nsftl_status_t status)
{
    if ((*report) == NULL)
    {
        return NSFTL_TEST_REPORT_NOT_INITIALIZED;
    }

    if (message_length >= NSFTL_TEST_REPORT_MAX_MESSAGE_LENGTH)
    {
        return NSFTL_REPORT_MESSAGE_IS_TOO_LONG;
    }

    if((*report)->message != NULL)
    {
        free((void*)(*report)->message);
        (*report)->message = NULL;
    }

    (*report)->message = (const char*) malloc((message_length+1) * sizeof(const char));
    if((*report)->message == NULL)
    {
        free((void*) *report);
        *report = NULL;
        return NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT;
    }

    memset((void*) (*report)->message, 0, message_length + 1);
    strncpy((char*) (*report)->message, message, message_length);
    ((char*)(*report)->message)[message_length] = '\0';

    (*report)->status = status;

    return NSFTL_SUCCESS;
}

/**
 * @brief 
 * 
 * @param test_unit 
 * @param test_callback_fn 
 * @return nsftl_status_t 
 */
nsftl_status_t nsftl_submit_test_to_test_unit (nsftl_test_unit_t test_unit, void (*test_callback_fn)(nsftl_test_report_t* test_report, nsftl_index_t index))
{
    if (test_unit == NULL)
    {
        return NSFTL_TEST_UNIT_NOT_INITIALIZED;
    }

    test_unit->test_callback_fn = test_callback_fn;
    if (test_unit->test_callback_fn == NULL)
    {
        return NSFTL_UNABLE_TO_SUBMIT_TEST_FUNCTION_TO_TEST_UNIT;
    }

    return NSFTL_SUCCESS;
}