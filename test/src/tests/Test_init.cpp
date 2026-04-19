#include <Test.hpp>
#include <test_init.h>
#include <test_destroy.h>
#include <test_utils.h>
#include <types/test_category_type.h>
#include <miscellaneous/test_statuses.h>
#include <defs.hpp>
#include <string>

void Test::init_category(mytest_report_type_t& report)
{
    mytest_test_category_t test_category = nullptr;
    std::string report_message;
    uint32_t status = mytest_init_test_category(&test_category, "Test category");

    if (status == MYTEST_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
    {
        report_message = "Test failed due to memory allocation failure";
        mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        return;
    }
    
    if (status == MYTEST_SUCCESS)
    {
        report_message = "Test successfull";
        status = mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_SUCCEDED);

        if (status != MYTEST_SUCCESS)
        {
            report->status = test::TEST_FAILED;
        }
    }

    mytest_destroy_test_category(&test_category);
}

void Test::init_multiple_categories(mytest_report_type_t& report)
{
    mytest_test_category_t test_category[test::MAX_TEST_CATEGORIES_ARRAY_LENGTH] = {0};
    std::string report_message;
    uint32_t status = MYTEST_SUCCESS;

    for (uint32_t i = 0U; i < test::MAX_TEST_CATEGORIES_ARRAY_LENGTH; i++)
    {
        char temp_test_category_name[MYTEST_TEST_CATEGORY_MAX_NAME_LENGTH] = {0};
        std::snprintf(temp_test_category_name, std::string("Test Category n°: ").length() + 2, "Test Category n°: %u", i);
        status = mytest_init_test_category(&test_category[i], temp_test_category_name);

        if (status == MYTEST_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
        {
            report_message = "Test failed due to memory allocation failure";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            for (uint32_t j = 0U; j < i; j++)
            {
                mytest_destroy_test_category(&test_category[j]);
            }   
            return;
        }
    }
    
    if (status == MYTEST_SUCCESS)
    {
        report_message = "Test successfull";
        status = mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_SUCCEDED);

        if (status != MYTEST_SUCCESS)
        {
            report->status = test::TEST_FAILED;
        }
    }

    for (uint32_t i = 0U; i < test::MAX_TEST_CATEGORIES_ARRAY_LENGTH; i++)
    {
        mytest_destroy_test_category(&test_category[i]);
    }
}

void Test::init_test_unit(mytest_report_type_t& report)
{
    mytest_test_unit_t test_unit = nullptr;
    std::string report_message;
    uint32_t status = mytest_init_test_unit(&test_unit, "Test unit");
    
    if (status == MYTEST_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
    {
        report_message = "Test failed due to memory allocation failure";
        mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        return;
    }
    
    if (status == MYTEST_SUCCESS)
    {
        report_message = "Test successfull";
        status = mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_SUCCEDED);

        if (status != MYTEST_SUCCESS)
        {
            report->status = test::TEST_FAILED;
        }
    }

    mytest_destroy_test_unit(&test_unit);
}

void Test::init_multiple_test_units(mytest_report_type_t& report)
{
    mytest_test_unit_t test_unit[test::MAX_TEST_UNITS_ARRAY_LENGTH] = {0};
    std::string report_message;
    uint32_t status = MYTEST_SUCCESS;

    for (uint32_t i = 0U; i < test::MAX_TEST_UNITS_ARRAY_LENGTH; i++)
    {
        char temp_test_unit_name[MYTEST_TEST_UNIT_MAX_NAME_LENGTH] = {0};
        std::snprintf(temp_test_unit_name, std::string("Test Unit n°: ").length() + 2, "Test Unit n°: %u", i);
        status = mytest_init_test_unit(&test_unit[i], temp_test_unit_name);
    
        if (status == MYTEST_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
        {
            report_message = "Test failed due to memory allocation failure";
            mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            for (uint32_t j = 0U; j < i; j++)
            {
                mytest_destroy_test_unit(&test_unit[j]);
            }
            return;
        }
    }
    
    if (status == MYTEST_SUCCESS)
    {
        report_message = "Test successfull";
        status = mytest_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_SUCCEDED);

        if (status != MYTEST_SUCCESS)
        {
            report->status = test::TEST_FAILED;
        }
    }

    for (uint32_t i = 0U; i < test::MAX_TEST_UNITS_ARRAY_LENGTH; i++)
    {
        mytest_destroy_test_unit(&test_unit[i]);
    }
}