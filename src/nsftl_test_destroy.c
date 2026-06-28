#include <types/nsftl_test_category_type.h>
#include <nsftl_test_destroy.h>
#include <stdlib.h>

/**
 * @brief 
 * 
 * @param test_category 
 */
void nsftl_destroy_test_category (nsftl_test_category_t* test_category)
{
    if (test_category == NULL || *test_category == NULL) return;

    for (nsftl_index_t i = 0; i < (*test_category)->size; i++)
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

/**
 * @brief 
 * 
 * @param test_unit 
 */
void nsftl_destroy_test_unit (nsftl_test_unit_t* test_unit)
{
    if (test_unit == NULL || *test_unit == NULL) return;

    (*test_unit)->test_callback_fn = NULL;
    free(*test_unit);
    (*test_unit) = NULL;
}

/**
 * @brief 
 * 
 * @param test_report 
 */
void nsftl_destroy_test_report (nsftl_test_report_t* test_report)
{
    if (test_report == NULL || *test_report == NULL) return;

    if ((*test_report)->message != NULL)
    {
        free((void*) (*test_report)->message);
        (*test_report)->message = NULL;
    }

    if ((*test_report)->start_time != NULL)
    {
        free((void*) (*test_report)->start_time);
        (*test_report)->start_time = NULL;
    }

    if ((*test_report)->end_time != NULL)
    {
        free((void*) (*test_report)->end_time);
        (*test_report)->end_time = NULL;
    }

    free(*test_report);
    *test_report = NULL;
}