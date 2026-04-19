#include <miscellaneous/test_statuses.h>
#include <types/test_unit_type.h>
#include <test_utils.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

uint32_t mytest_write_report (mytest_report_type_t* report, const char* message,  size_t message_length, uint32_t status)
{
    if (message_length >= MYTEST_TEST_REPORT_MAX_MESSAGE_LENGTH)
    {
        return MYTEST_REPORT_MESSAGE_IS_TOO_LONG;
    }

    *report = (mytest_report_type_t) malloc(sizeof(mytest_report_type));
    if ((*report) == NULL)
    {
        return MYTEST_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT;
    }

    (*report)->message = (const char*) malloc((message_length+1) * sizeof(const char));
    if((*report)->message == NULL)
    {
        free((void*) *report);
        *report = NULL;
        return MYTEST_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT;
    }

    memset((void*) (*report)->message, 0, message_length + 1);
    strncpy((char*) (*report)->message, message, message_length);
    (*report)->status = status;

    return MYTEST_SUCCESS;
}

uint32_t mytest_submit_test_to_test_unit (mytest_test_unit_t test_unit, void (*test_callback_fn)(mytest_report_type_t* test_report, uint32_t index))
{
    test_unit->test_callback_fn = test_callback_fn;
    if (test_unit->test_callback_fn == NULL)
    {
        return MYTEST_UNABLE_TO_SUBMIT_TEST_FUNCTION_TO_TEST_UNIT;
    }

    return MYTEST_SUCCESS;
}