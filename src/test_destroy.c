#include <types/test_category_type.h>
#include <test_destroy.h>
#include <stdlib.h>

void mytest_destroy_test_category (mytest_test_category_t* test_category)
{
    if (test_category == NULL || *test_category == NULL) return;

    for (uint32_t i = 0; i < (*test_category)->size; i++)
    {
        (*test_category)->tests[i].test_callback_fn = NULL;
        if ((*test_category)->reports[i].message != NULL)
        {
            free((void*) (*test_category)->reports[i].message);
            (*test_category)->reports[i].message = NULL;
        }
        
    }

    if ((*test_category)->reports != NULL)
    {
        free((*test_category)->reports);
        (*test_category)->reports = NULL;
    }
    if ((*test_category)->tests != NULL)
    {
        free((*test_category)->tests);
        (*test_category)->tests = NULL;
    }

    free(*test_category);
    *test_category = NULL;
}

void mytest_destroy_test_unit (mytest_test_unit_t* test_unit)
{
    if (test_unit == NULL || *test_unit == NULL) return;

    (*test_unit)->test_callback_fn = NULL;
    free(*test_unit);
    (*test_unit) = NULL;
}

void mytest_destroy_test_report (mytest_report_type_t* test_report)
{
    if (test_report == NULL || *test_report == NULL) return;

    if ((*test_report)->message != NULL)
    {
        free((void*) (*test_report)->message);
        (*test_report)->message = NULL;
    }

    free(*test_report);
    *test_report = NULL;
}