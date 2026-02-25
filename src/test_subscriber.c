#include <test_defs.h>
#include <types/test_category_type.h>
#include <test_subscriber.h>
#include <stdlib.h>
#include <string.h>

void mytest_init_test_category (mytest_test_category** test_category)
{
    mytest_test_unit *test_units = (mytest_test_unit*) malloc(sizeof(mytest_test_unit) * MYTEST_DEFAULT_TESTS_ARRAY_SIZE);
    mytest_report_type *test_reports = (mytest_report_type*) malloc(sizeof(mytest_report_type) * MYTEST_DEFAULT_TESTS_ARRAY_SIZE);

    *test_category = (mytest_test_category*)malloc(sizeof(mytest_test_category));
    (*test_category)->reports = test_reports;
    (*test_category)->tests = test_units;
    (*test_category)->capacity = MYTEST_DEFAULT_TESTS_ARRAY_SIZE;
    (*test_category)->size = 0U;
}

void mytest_subscribe_test_unit (mytest_test_category* test_category, mytest_test_unit* test_unit)
{
    if (test_category->size < test_category->capacity)
    {
        test_category->tests[test_category->size] = *test_unit;
        test_category->size++;
    }
    else
    {
        test_category->capacity = test_category->capacity + 10U;
        test_category->tests = (mytest_test_unit*) realloc(test_category->tests, test_category->capacity);
        test_category->reports = (mytest_report_type*) realloc(test_category->reports, test_category->capacity);
        test_category->tests[test_category->size] = *test_unit;
        
        test_category->size++;
    }
}

void mytest_execute_category_tests (mytest_test_category* test_category)
{
    mytest_report_type* test_report = (mytest_report_type*) malloc(sizeof(mytest_report_type));
    for (uint32_t i = 0U; i < test_category->size; i++)
    {
        test_category->tests[i].test_callback_fn(test_report);
        
        if (test_report->message != NULL)
        {
            test_category->reports[i].message = test_report->message;
        }
        else
        {
            test_category->reports[i].message = "";
        }
    }
    free(test_report);
}

void mytest_destroy_test_category (mytest_test_category* test_category)
{
    free(test_category->reports);
    free(test_category->tests);
    free(test_category);
}

mytest_report_type mytest_write_report (const char* message, size_t message_length, int status)
{
    return (mytest_report_type){
        .message = message,
        .status = status
    };
}