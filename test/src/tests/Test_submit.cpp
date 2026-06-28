#include <Test.hpp>
#include <nsftl_test_subscriber.h>
#include <nsftl_test_init.h>
#include <nsftl_test_destroy.h>
#include <nsftl_test_utils.h>
#include <types/nsftl_test_category_type.h>
#include <miscellaneous/nsftl_test_statuses.h>
#include <defs.hpp>
#include <iostream>
#include <string>

void Test::submit_tests_collection()
{
    nsftl_test_report_t report = nullptr;

    std::cout << "### TEST:SUBMIT TEST TO SINGLE TEST UNIT" << std::endl;
    if(this->init_report(report) == NSFTL_SUCCESS)
    {
        this->start_report_timer(report);
        this->submit_test_to_single_test_unit(report);
        this->stop_report_timer(report);
    }
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:SUBMIT TEST TO MULTIPLE TEST UNITS" << std::endl;
    if(this->init_report(report) == NSFTL_SUCCESS)
    {
        this->start_report_timer(report);
        this->submit_test_to_multiple_test_units(report);
        this->stop_report_timer(report);
    }
    this->print_test_report(report);
    this->destroy_report(report);
}

void Test::submit_test_to_single_test_unit(nsftl_test_report_t& report)
{
    nsftl_test_unit_t test_unit = nullptr;
    std::string report_message;
    uint32_t status = nsftl_init_test_unit(&test_unit, "Test unit");
    
    if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
    {
        report_message = "Test failed due to memory allocation failure during test_unit initialization";
        nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        return;
    }

    status = nsftl_submit_test_to_test_unit(test_unit, Test::test_callback_fn);

    if (status == NSFTL_UNABLE_TO_SUBMIT_TEST_FUNCTION_TO_TEST_UNIT)
    {
        report_message = "Test failed due to inability to submit the test function to the test unit";
        nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        nsftl_destroy_test_unit(&test_unit);
        return;
    }

    if (status == NSFTL_SUCCESS)
    {
        report_message = "Test successfull";
        status = nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_SUCCEDED);

        if (status != NSFTL_SUCCESS)
        {
            report->status = test::TEST_FAILED;
        }
    }

    nsftl_destroy_test_unit(&test_unit);
}

void Test::submit_test_to_multiple_test_units(nsftl_test_report_t& report)
{
    nsftl_test_unit_t test_unit[test::MAX_TEST_UNITS_ARRAY_LENGTH] = {0};
    std::string report_message;
    uint32_t status = NSFTL_SUCCESS;

    for (uint32_t i = 0U; i < test::MAX_TEST_UNITS_ARRAY_LENGTH; i++)
    {
        char temp_test_unit_name[NSFTL_TEST_UNIT_MAX_NAME_LENGTH] = {0};
        std::snprintf(temp_test_unit_name, std::string("Test Unit n°: ").length() + 2, "Test Unit n°: %u", i);
        status = nsftl_init_test_unit(&test_unit[i], temp_test_unit_name);
    
        if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
        {
            report_message = "Test failed due to memory allocation failure";
            nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            for (uint32_t j = 0U; j < i; j++)
            {
                nsftl_destroy_test_unit(&test_unit[j]);
            }
            return;
        }

        status = nsftl_submit_test_to_test_unit(test_unit[i], Test::test_callback_fn);

        if (status == NSFTL_UNABLE_TO_SUBMIT_TEST_FUNCTION_TO_TEST_UNIT)
        {
            report_message = "Test failed due to inability to submit the test function to the test unit";
            nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            for (uint32_t j = 0U; j <= i; j++)
            {
                nsftl_destroy_test_unit(&test_unit[j]);
            }
            return;
        }
    }
    
    if (status == NSFTL_SUCCESS)
    {
        report_message = "Test successfull";
        status = nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_SUCCEDED);

        if (status != NSFTL_SUCCESS)
        {
            report->status = test::TEST_FAILED;
        }
    }

    for (uint32_t i = 0U; i < test::MAX_TEST_UNITS_ARRAY_LENGTH; i++)
    {
        nsftl_destroy_test_unit(&test_unit[i]);
    }
}