#include <types/nsftl_test_category_type.h>
#include <miscellaneous/nsftl_test_statuses.h>
#include <nsftl_test_execute.h>
#include <nsftl_test_destroy.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief 
 * 
 * @param test_category 
 * @param index 
 * @return nsftl_status_t 
 */
nsftl_status_t nsftl_execute_category_test (nsftl_test_category_t test_category, nsftl_index_t index)
{
    if (test_category == NULL)
    {
        return NSFTL_TEST_CATEGORY_NOT_INITIALIZED;
    }

    if (test_category->reports == NULL)
    {
        return NSFTL_TEST_CATEGORY_REPORT_ARRAY_NOT_INITIALIZED;
    }

    if (index >= test_category->size)
    {
        return NSFTL_TEST_INDEX_BIGGER_THAN_CATEGORY_SIZE;
    }

    nsftl_test_report_t test_report = NULL;
    test_category->tests[index].test_callback_fn(&test_report, index);

    if (test_category->reports[index].message != NULL)
    {
        free((void*) test_category->reports[index].message);
        test_category->reports[index].message = NULL;
    }

    if (test_report == NULL || test_report->message == NULL)
    {
        char* temp_report_message = strdup("");
        if (temp_report_message == NULL)
        {
            nsftl_destroy_test_report(&test_report);

            return NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT;
        }

        test_category->reports[index].message = (const char*) temp_report_message;
    }
    else
    {
        size_t msg_len = strnlen(test_report->message, NSFTL_TEST_REPORT_MAX_MESSAGE_LENGTH);
        if (msg_len >= NSFTL_TEST_REPORT_MAX_MESSAGE_LENGTH)
        {
            nsftl_destroy_test_report(&test_report);

            return NSFTL_REPORT_MESSAGE_IS_TOO_LONG;
        }

        char* temp_report_message = (char*) malloc((msg_len + 1) * sizeof(char));
        if (temp_report_message == NULL)
        {
            nsftl_destroy_test_report(&test_report);

            return NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT;
        }

        memset((void*) temp_report_message, 0, msg_len + 1);
        strncpy(temp_report_message, test_report->message, msg_len);
        temp_report_message[msg_len] = '\0';

        test_category->reports[index].message = (const char*) temp_report_message;
    }

    nsftl_destroy_test_report(&test_report);
    
    return NSFTL_SUCCESS;
}