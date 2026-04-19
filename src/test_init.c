#include <miscellaneous/test_statuses.h>
#include <types/test_category_type.h>
#include <test_init.h>
#include <stdlib.h>
#include <string.h>

uint32_t mytest_init_test_category (mytest_test_category_t* test_category, const char* test_category_name)
{
    *test_category = (mytest_test_category_t)malloc(sizeof(**test_category));
    if (*test_category == NULL)
    {
        return MYTEST_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT;
    }

    mytest_test_unit_t test_units = (mytest_test_unit_t) calloc(MYTEST_DEFAULT_TESTS_ARRAY_SIZE, sizeof(*test_units));
    if (test_units == NULL)
    {
        free(*test_category);
        (*test_category) = NULL;
        return MYTEST_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT;
    }

    mytest_report_type_t test_reports = (mytest_report_type_t) calloc(MYTEST_DEFAULT_TESTS_ARRAY_SIZE, sizeof(*test_reports));
    if (test_reports == NULL)
    {
        free(*test_category);
        (*test_category) = NULL;
        free(test_units);
        test_units = NULL;
        return MYTEST_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT;
    }

    /**
     * @note
     * I want to be sure that the const char[] passed as test_category_name is actually a string, so I init every element to 0 with memset.
     * This forces the const char[] to be a string, even if its length is MYTEST_TEST_CATEGORY_MAX_NAME_LENGTH or more.
     */
    memset((void*) (*test_category)->category_name, 0, MYTEST_TEST_CATEGORY_MAX_NAME_LENGTH + 1);
    strncpy((char*) (*test_category)->category_name, (const char*) test_category_name, MYTEST_TEST_CATEGORY_MAX_NAME_LENGTH);

    (*test_category)->reports = test_reports;
    (*test_category)->tests = test_units;
    (*test_category)->capacity = MYTEST_DEFAULT_TESTS_ARRAY_SIZE;
    (*test_category)->size = 0U;
    return MYTEST_SUCCESS;
}

uint32_t mytest_init_test_unit (mytest_test_unit_t* test_unit, const char* test_unit_name)
{
    *test_unit = (mytest_test_unit_t) malloc(sizeof(**test_unit));

    if (*test_unit == NULL)
    {
        return MYTEST_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT;
    }
    
    /**
     * @note
     * I want to be sure that the const char[] passed as test_unit_name is actually a string, so I init every element to 0 with memset.
     * This forces the const char[] to be a string, even if its length is MYTEST_TEST_UNIT_MAX_NAME_LENGTH or more.
     */
    memset((void*) (*test_unit)->test_name, 0, MYTEST_TEST_UNIT_MAX_NAME_LENGTH + 1);
    strncpy((char*) (*test_unit)->test_name, (const char*) test_unit_name, MYTEST_TEST_UNIT_MAX_NAME_LENGTH + 1);

    return MYTEST_SUCCESS;
}