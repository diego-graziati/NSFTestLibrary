#include <types/test_category_type.h>
#include <miscellaneous/test_statuses.h>
#include <test_execute.h>
#include <stdlib.h>
#include <string.h>

uint32_t mytest_execute_category_test (mytest_test_category_t test_category, uint32_t index)
{
    if (test_category == NULL)
    {
        return MYTEST_TEST_CATEGORY_NOT_INITIALIZED;
    }

    if (test_category->reports == NULL)
    {
        return MYTEST_TEST_CATEGORY_REPORT_ARRAY_NOT_INITIALIZED;
    }

    if (index >= test_category->size)
    {
        return MYTEST_TEST_INDEX_BIGGER_THAN_CATEGORY_SIZE;
    }

    mytest_report_type_t test_report = NULL;
    test_category->tests[index].test_callback_fn(&test_report, index);

    if (test_category->reports[index].message != NULL)
    {
        free((void*) test_category->reports[index].message);
        test_category->reports[index].message = NULL;
    }

    if (test_report == NULL || test_report->message == NULL)
    {
        char* temp_report_message = (char*) malloc(1 * sizeof(char));
        if (temp_report_message == NULL)
        {
            if (test_report != NULL)
            {
                free((void*) test_report);
                test_report = NULL;
            }

            return MYTEST_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT;
        }

        memset((void*) temp_report_message, 0, 1);
        test_category->reports[index].message = (const char*) temp_report_message;
    }
    else
    {
        if (strnlen(test_report->message, MYTEST_TEST_REPORT_MAX_MESSAGE_LENGTH) == (MYTEST_TEST_REPORT_MAX_MESSAGE_LENGTH + 1))
        {
            free((void*) test_report);
            test_report = NULL;
            return MYTEST_REPORT_MESSAGE_IS_TOO_LONG;
        }

        test_category->reports[index].message = (const char*) malloc((strlen(test_report->message) + 1) * sizeof(const char));
        if (test_category->reports[index].message == NULL)
        {
            free((void*) test_report->message);
            test_report->message = NULL;
            free((void*) test_report);
            test_report = NULL;
            return MYTEST_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT;
        }

        memset((void*) test_category->reports[index].message, 0, strnlen(test_report->message, MYTEST_TEST_REPORT_MAX_MESSAGE_LENGTH) + 1);
        strncpy((char*) test_category->reports[index].message, test_report->message, strnlen(test_report->message, MYTEST_TEST_REPORT_MAX_MESSAGE_LENGTH));
    }


    free((void*) test_report->message);
    test_report->message = NULL;
    free((void*) test_report);
    test_report = NULL;
    return MYTEST_SUCCESS;
}