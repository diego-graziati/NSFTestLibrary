#include <Test.hpp>
#include <nsftl_test_subscriber.h>
#include <nsftl_test_init.h>
#include <nsftl_test_execute.h>
#include <nsftl_test_destroy.h>
#include <nsftl_test_utils.h>
#include <types/nsftl_test_category_type.h>
#include <miscellaneous/nsftl_test_statuses.h>
#include <defs.hpp>
#include <string>

void Test::execute_category_with_single_unit(nsftl_report_type_t& report)
{
    // SINGLE TEST CATEGORY AND TEST UNIT INITIALIZATION
    nsftl_test_category_t test_category = nullptr;
    std::string report_message;
    uint32_t status = mynsftl_test_init_test_category(&test_category, "Test category");

    if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
    {
        report_message = "Test failed due to memory allocation failure during test_category initialization";
        mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        return;
    }

    nsftl_test_unit_t test_unit = nullptr;
    status = mynsftl_test_init_test_unit(&test_unit, "Test unit");
    if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
    {
        report_message = "Test failed due to memory allocation failure during test_unit initialization";
        mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        mynsftl_test_destroy_test_category(&test_category);
        return;
    }

    // TEST SUBMIT TO TEST UNIT
    status = mytest_submit_test_to_test_unit(test_unit, Test::test_callback_fn);

    if (status == NSFTL_UNABLE_TO_SUBMIT_TEST_FUNCTION_TO_TEST_UNIT)
    {
        report_message = "Test failed due to inability to submit the test function to the test unit";
        mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        mynsftl_test_destroy_test_category(&test_category);
        mynsftl_test_destroy_test_unit(&test_unit);
        return;
    }

    // SINGLE TEST UNIT SUBSCRIPTION
    status = mytest_subscribe_test_unit(test_category, &test_unit);

    if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
    {
        report_message = "Test failed due to memory allocation failure during the test_unit subscription to the test_category";
        mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        mynsftl_test_destroy_test_category(&test_category);
        mynsftl_test_destroy_test_unit(&test_unit);
        return;
    }

    // SINGLE TEST CATEGORY EXECUTION
    status = mynsftl_test_execute_category_test(test_category, 0);

    if (status == NSFTL_TEST_CATEGORY_NOT_INITIALIZED)
    {
        report_message = "The test category hasn't been initialized! Unable to execute";
        mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        mynsftl_test_destroy_test_category(&test_category);
        return;
    }

    if (status == NSFTL_TEST_CATEGORY_REPORT_ARRAY_NOT_INITIALIZED)
    {
        report_message = "The test category's reports array hasn't been initialized! Unable to execute!";
        mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        mynsftl_test_destroy_test_category(&test_category);
        return;
    }

    if (status == NSFTL_TEST_INDEX_BIGGER_THAN_CATEGORY_SIZE)
    {
        report_message = "The specified test unit index exceeds the test category's tests array size! Unable to execute!";
        mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        mynsftl_test_destroy_test_category(&test_category);
        return;
    }

    if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
    {
        report_message = "Unable to successfully allocate memory during test unit execution! Unable to execute!";
        mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        mynsftl_test_destroy_test_category(&test_category);
        return;
    }

    if (status == NSFTL_REPORT_MESSAGE_IS_TOO_LONG)
    {
        report_message = "The test report's message exceeds the allowed length! Unable to execute!";
        mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        mynsftl_test_destroy_test_category(&test_category);
        return;
    }

    if (status == NSFTL_SUCCESS)
    {
        report_message = "Test successfull";
        status = mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_SUCCEDED);

        if (status != NSFTL_SUCCESS)
        {
            report->status = test::TEST_FAILED;
        }
    }

    mynsftl_test_destroy_test_category(&test_category);
}

void Test::execute_category_with_multiple_units(nsftl_report_type_t& report)
{
    nsftl_test_category_t test_category = nullptr;
    std::string report_message;
    uint32_t status = mynsftl_test_init_test_category(&test_category, "Test category");

    if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
    {
        report_message = "Test failed due to memory allocation failure during test_category initialization";
        mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        return;
    }

    nsftl_test_unit_t test_unit = nullptr;
    for (uint32_t i = 0U; i < test::MAX_TEST_UNITS_ARRAY_LENGTH; i++)
    {
        char temp_test_unit_name[NSFTL_TEST_UNIT_MAX_NAME_LENGTH] = {0};
        std::snprintf(temp_test_unit_name, std::string("Test Unit n°: ").length() + 2, "Test Unit n°: %u", i);
        status = mynsftl_test_init_test_unit(&test_unit, temp_test_unit_name);
        if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
        {
            report_message = "Test failed due to memory allocation failure during test_unit initialization";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            mynsftl_test_destroy_test_category(&test_category);
            return;
        }

        status = mytest_submit_test_to_test_unit(test_unit, Test::multiple_tests_callback_fn);

        if (status == NSFTL_UNABLE_TO_SUBMIT_TEST_FUNCTION_TO_TEST_UNIT)
        {
            report_message = "Test failed due to inability to submit the test function to the test unit";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            mynsftl_test_destroy_test_category(&test_category);
            mynsftl_test_destroy_test_unit(&test_unit);
            return;
        }

        status = mytest_subscribe_test_unit(test_category, &test_unit);

        if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
        {
            report_message = "Test failed due to memory allocation failure during the test_unit subscription to the test_category";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            mynsftl_test_destroy_test_category(&test_category);
            mynsftl_test_destroy_test_unit(&test_unit);
            return;
        }
    }

    for (uint32_t i = 0U; i < 30; i++)
    {
        status = mynsftl_test_execute_category_test(test_category, i);

        if (status == NSFTL_TEST_CATEGORY_NOT_INITIALIZED)
        {
            report_message = "The test category hasn't been initialized! Unable to execute";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            mynsftl_test_destroy_test_category(&test_category);
            return;
        }

        if (status == NSFTL_TEST_CATEGORY_REPORT_ARRAY_NOT_INITIALIZED)
        {
            report_message = "The test category's reports array hasn't been initialized! Unable to execute!";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            mynsftl_test_destroy_test_category(&test_category);
            return;
        }

        if (status == NSFTL_TEST_INDEX_BIGGER_THAN_CATEGORY_SIZE)
        {
            report_message = "The specified test unit index exceeds the test category's tests array size! Unable to execute!";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            mynsftl_test_destroy_test_category(&test_category);
            return;
        }

        if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
        {
            report_message = "Unable to successfully allocate memory during test unit execution! Unable to execute!";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            mynsftl_test_destroy_test_category(&test_category);
            return;
        }

        if (status == NSFTL_REPORT_MESSAGE_IS_TOO_LONG)
        {
            report_message = "The test report's message exceeds the allowed length! Unable to execute!";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            mynsftl_test_destroy_test_category(&test_category);
            return;
        }
    }

    if (status == NSFTL_SUCCESS)
    {
        report_message = "Test successfull";
        status = mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_SUCCEDED);

        if (status != NSFTL_SUCCESS)
        {
            report->status = test::TEST_FAILED;
        }
    }

    mynsftl_test_destroy_test_category(&test_category);
}

void Test::execute_multiple_categories_with_single_unit(nsftl_report_type_t& report)
{
    nsftl_test_category_t test_category[test::MAX_TEST_CATEGORIES_ARRAY_LENGTH] = {0};
    nsftl_test_unit_t test_unit = nullptr;
    std::string report_message;
    uint32_t status = NSFTL_SUCCESS;

    for (uint32_t i = 0U; i < test::MAX_TEST_CATEGORIES_ARRAY_LENGTH; i++)
    {
        char temp_test_category_name[NSFTL_TEST_CATEGORY_MAX_NAME_LENGTH] = {0};
        std::snprintf(temp_test_category_name, std::string("Test Category n°: ").length() + 2, "Test Category n°: %u", i);
        status = mynsftl_test_init_test_category(&test_category[i], temp_test_category_name);

        if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
        {
            report_message = "Test failed due to memory allocation failure";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            for (uint32_t j = 0U; j < i; j++)
            {
                mynsftl_test_destroy_test_category(&test_category[j]);
            }   
            return;
        }

        mynsftl_test_init_test_unit(&test_unit, "Test unit");
    
        if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
        {
            report_message = "Test failed due to memory allocation failure during test_unit initialization";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            for (uint32_t j = 0U; j <= i; j++)
            {
                mynsftl_test_destroy_test_category(&test_category[j]);
            }
            return;
        }

        status = mytest_submit_test_to_test_unit(test_unit, Test::test_callback_fn);

        if (status == NSFTL_UNABLE_TO_SUBMIT_TEST_FUNCTION_TO_TEST_UNIT)
        {
            report_message = "Test failed due to inability to submit the test function to the test unit";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            mynsftl_test_destroy_test_unit(&test_unit);
            for (uint32_t j = 0U; j <= i; j++)
            {
                mynsftl_test_destroy_test_category(&test_category[j]);
            }
            return;
        }

        status = mytest_subscribe_test_unit(test_category[i], &test_unit);

        if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
        {
            report_message = "Test failed due to memory allocation failure";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            mynsftl_test_destroy_test_unit(&test_unit);
            for (uint32_t j = 0U; j <= i; j++)
            {
                mynsftl_test_destroy_test_category(&test_category[j]);
            }
            return;
        }
    }

    for (uint32_t i = 0U; i < test::MAX_TEST_CATEGORIES_ARRAY_LENGTH; i++)
    {
        status = mynsftl_test_execute_category_test(test_category[i], 0);

        if (status != NSFTL_SUCCESS)
        {
            report->status = test::TEST_FAILED;
        }

        if (status == NSFTL_TEST_CATEGORY_NOT_INITIALIZED)
        {
            report_message = "The test category hasn't been initialized! Unable to execute";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            for (uint32_t j = 0U; j <= i; j++)
            {
                mynsftl_test_destroy_test_category(&test_category[j]);
            }
            return;
        }

        if (status == NSFTL_TEST_CATEGORY_REPORT_ARRAY_NOT_INITIALIZED)
        {
            report_message = "The test category's reports array hasn't been initialized! Unable to execute!";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            for (uint32_t j = 0U; j <= i; j++)
            {
                mynsftl_test_destroy_test_category(&test_category[j]);
            }
            return;
        }

        if (status == NSFTL_TEST_INDEX_BIGGER_THAN_CATEGORY_SIZE)
        {
            report_message = "The specified test unit index exceeds the test category's tests array size! Unable to execute!";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            for (uint32_t j = 0U; j <= i; j++)
            {
                mynsftl_test_destroy_test_category(&test_category[j]);
            }
            return;
        }

        if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
        {
            report_message = "Unable to successfully allocate memory during test unit execution! Unable to execute!";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            for (uint32_t j = 0U; j <= i; j++)
            {
                mynsftl_test_destroy_test_category(&test_category[j]);
            }
            return;
        }

        if (status == NSFTL_REPORT_MESSAGE_IS_TOO_LONG)
        {
            report_message = "The test report's message exceeds the allowed length! Unable to execute!";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            for (uint32_t j = 0U; j <= i; j++)
            {
                mynsftl_test_destroy_test_category(&test_category[j]);
            }
            return;
        }
    }
    
    if (status == NSFTL_SUCCESS)
    {
        report_message = "Test successfull";
        status = mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_SUCCEDED);

        if (status != NSFTL_SUCCESS)
        {
            report->status = test::TEST_FAILED;
        }
    }

    for (uint32_t i = 0U; i < test::MAX_TEST_CATEGORIES_ARRAY_LENGTH; i++)
    {
        mynsftl_test_destroy_test_category(&test_category[i]);
    }
}

void Test::execute_multiple_categories_with_multiple_units(nsftl_report_type_t& report)
{
    nsftl_test_category_t test_category[test::MAX_TEST_CATEGORIES_ARRAY_LENGTH] = {0};
    std::string report_message;
    uint32_t status = NSFTL_SUCCESS;

    for (uint32_t i = 0U; i < test::MAX_TEST_CATEGORIES_ARRAY_LENGTH; i++)
    {
        nsftl_test_unit_t test_unit[test::MAX_TEST_CATEGORIES_ARRAY_LENGTH] = {0};
        char temp_test_category_name[NSFTL_TEST_CATEGORY_MAX_NAME_LENGTH] = {0};
        std::snprintf(temp_test_category_name, std::string("Test Category n°: ").length() + 2, "Test Category n°: %u", i);
        status = mynsftl_test_init_test_category(&test_category[i], temp_test_category_name);

        if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
        {
            report_message = "Test failed due to memory allocation failure";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            for (uint32_t j = 0U; j < i; j++)
            {
                mynsftl_test_destroy_test_category(&test_category[j]);
            }
            return;
        }

        for (uint32_t j = 0U; j < test::MAX_TEST_UNITS_ARRAY_LENGTH; j++)
        {
            char temp_test_unit_name[NSFTL_TEST_UNIT_MAX_NAME_LENGTH] = {0};
            std::snprintf(temp_test_unit_name, std::string("Test Unit n°: ").length() + 2, "Test Unit n°: %u", i);
            status = mynsftl_test_init_test_unit(&test_unit[j], temp_test_unit_name);
        
            if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
            {
                report_message = "Test failed due to memory allocation failure";
                mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
                for (uint32_t k = 0U; k < j; k++)
                {
                    mynsftl_test_destroy_test_unit(&test_unit[k]);
                }
                for (uint32_t k = 0U; k <= i; k++)
                {
                    mynsftl_test_destroy_test_category(&test_category[k]);
                }
                return;
            }

            status = mytest_submit_test_to_test_unit(test_unit[j], Test::test_callback_fn);

            if (status == NSFTL_UNABLE_TO_SUBMIT_TEST_FUNCTION_TO_TEST_UNIT)
            {
                report_message = "Test failed due to inability to submit the test function to the test unit";
                mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
                for (uint32_t k = 0U; k <= j; k++)
                {
                    mynsftl_test_destroy_test_unit(&test_unit[k]);
                }
                for (uint32_t k = 0U; k <= i; k++)
                {
                    mynsftl_test_destroy_test_category(&test_category[k]);
                }
                return;
            }

            status = mytest_subscribe_test_unit(test_category[i], &test_unit[j]);

            if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
            {
                report_message = "Test failed due to memory allocation failure during test unit subscription to test category";
                mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
                for (uint32_t k = 0U; k <= j; k++)
                {
                    mynsftl_test_destroy_test_unit(&test_unit[k]);
                }
                for (uint32_t k = 0U; k <= i; k++)
                {
                    mynsftl_test_destroy_test_category(&test_category[k]);
                }
                return;
            }
        }
    }

    for (uint32_t i = 0U; i < test::MAX_TEST_CATEGORIES_ARRAY_LENGTH; i++)
    {
        for (uint32_t j = 0U; j < test::MAX_TEST_UNITS_ARRAY_LENGTH; j++)
        {
            status = mynsftl_test_execute_category_test(test_category[i], j);

            if (status == NSFTL_TEST_CATEGORY_NOT_INITIALIZED)
            {
                report_message = "The test category hasn't been initialized! Unable to execute";
                mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
                for (uint32_t k = 0U; k <= i; k++)
                {
                    mynsftl_test_destroy_test_category(&test_category[k]);
                }
                return;
            }

            if (status == NSFTL_TEST_CATEGORY_REPORT_ARRAY_NOT_INITIALIZED)
            {
                report_message = "The test category's reports array hasn't been initialized! Unable to execute!";
                mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
                for (uint32_t k = 0U; k <= i; k++)
                {
                    mynsftl_test_destroy_test_category(&test_category[k]);
                }
                return;
            }

            if (status == NSFTL_TEST_INDEX_BIGGER_THAN_CATEGORY_SIZE)
            {
                report_message = "The specified test unit index exceeds the test category's tests array size! Unable to execute!";
                mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
                for (uint32_t k = 0U; k <= i; k++)
                {
                    mynsftl_test_destroy_test_category(&test_category[k]);
                }
                return;
            }

            if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
            {
                report_message = "Unable to successfully allocate memory during test unit execution! Unable to execute!";
                mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
                for (uint32_t k = 0U; k <= i; k++)
                {
                    mynsftl_test_destroy_test_category(&test_category[k]);
                }
                return;
            }

            if (status == NSFTL_REPORT_MESSAGE_IS_TOO_LONG)
            {
                report_message = "The test report's message exceeds the allowed length! Unable to execute!";
                mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
                for (uint32_t k = 0U; k <= i; k++)
                {
                    mynsftl_test_destroy_test_category(&test_category[k]);
                }
                return;
            }
        }
    }
    
    if (status == NSFTL_SUCCESS)
    {
        report_message = "Test successfull";
        status = mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_SUCCEDED);

        if (status != NSFTL_SUCCESS)
        {
            report->status = test::TEST_FAILED;
        }
    }

    for (uint32_t i = 0U; i < test::MAX_TEST_CATEGORIES_ARRAY_LENGTH; i++)
    {
        mynsftl_test_destroy_test_category(&test_category[i]);
    }
}