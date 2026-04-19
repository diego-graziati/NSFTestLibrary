#include <types/test_category_type.h>
#include <miscellaneous/test_statuses.h>
#include <test_subscriber.h>
#include <stdlib.h>
#include <string.h>

uint32_t mytest_subscribe_test_unit (mytest_test_category_t test_category, mytest_test_unit_t* test_unit)
{
    if (test_category->size >= test_category->capacity)
    {
        uint32_t new_capacity = test_category->capacity + 10U;
        mytest_test_unit_t temp_tests = (mytest_test_unit_t) malloc(new_capacity * sizeof(*test_category->tests));
        if (temp_tests == NULL)
        {
            return MYTEST_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT;
        }

        mytest_report_type_t temp_reports = (mytest_report_type_t) malloc(new_capacity * sizeof(*test_category->reports));
        if (temp_reports == NULL)
        {
            free((void*) temp_tests);
            temp_tests = NULL;
            return MYTEST_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT;
        }

        memcpy(temp_tests, test_category->tests, test_category->capacity * sizeof(*test_category->tests));
        memset(temp_tests + test_category->capacity, 0, (new_capacity - test_category->capacity) * sizeof(*temp_tests));

        memcpy(temp_reports, test_category->reports, test_category->capacity * sizeof(*test_category->reports));
        memset(temp_reports + test_category->capacity, 0, (new_capacity - test_category->capacity) * sizeof(*temp_reports));
        
        free((void*) test_category->tests);
        free((void*) test_category->reports);

        test_category->tests = temp_tests;
        test_category->reports = temp_reports;

        test_category->capacity = new_capacity;
        
    }
    strncpy((char*) test_category->tests[test_category->size].test_name, (const char*) (*test_unit)->test_name, MYTEST_TEST_UNIT_MAX_NAME_LENGTH);
    test_category->tests[test_category->size].test_callback_fn = (*test_unit)->test_callback_fn;

    test_category->size++;
    
    free((void*) *test_unit);
    (*test_unit) = NULL;
    return MYTEST_SUCCESS;
}

