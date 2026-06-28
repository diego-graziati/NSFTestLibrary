#include <Test.hpp>
#include <nsftl_test_init.h>
#include <nsftl_test_destroy.h>
#include <nsftl_test_utils.h>
#include <types/nsftl_test_category_type.h>
#include <miscellaneous/nsftl_test_statuses.h>
#include <defs.hpp>
#include <iostream>
#include <string>

void Test::init_tests_collection()
{
    nsftl_test_report_t report = nullptr;

    std::cout << "### TEST:INIT CATEGORY" << std::endl;
    if(this->init_report(report) == NSFTL_SUCCESS)
    {
        this->start_report_timer(report);
        this->init_category(report);
        this->stop_report_timer(report);
    }
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:INIT MULTIPLE CATEGORIES" << std::endl;
    if(this->init_report(report) == NSFTL_SUCCESS)
    {
        this->start_report_timer(report);
        this->init_multiple_categories(report);
        this->stop_report_timer(report);
    }
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:INIT TEST UNIT" << std::endl;
    if(this->init_report(report) == NSFTL_SUCCESS)
    {
        this->start_report_timer(report);
        this->init_test_unit(report);
        this->stop_report_timer(report);
    }
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:INIT MULTIPLE TEST UNITS" << std::endl;
    if(this->init_report(report) == NSFTL_SUCCESS)
    {
        this->start_report_timer(report);
        this->init_multiple_test_units(report);
        this->stop_report_timer(report);
    }
    this->print_test_report(report);
    this->destroy_report(report);
}

void Test::init_category(nsftl_test_report_t& report)
{
    nsftl_test_category_t test_category = nullptr;
    std::string report_message;
    uint32_t status = nsftl_init_test_category(&test_category, "Test category");

    if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
    {
        report_message = "Test failed due to memory allocation failure";
        nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
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

    nsftl_destroy_test_category(&test_category);
}

void Test::init_multiple_categories(nsftl_test_report_t& report)
{
    nsftl_test_category_t test_category[test::MAX_TEST_CATEGORIES_ARRAY_LENGTH] = {0};
    std::string report_message;
    uint32_t status = NSFTL_SUCCESS;

    for (uint32_t i = 0U; i < test::MAX_TEST_CATEGORIES_ARRAY_LENGTH; i++)
    {
        char temp_test_category_name[NSFTL_TEST_CATEGORY_MAX_NAME_LENGTH] = {0};
        std::snprintf(temp_test_category_name, std::string("Test Category n°: ").length() + 2, "Test Category n°: %u", i);
        status = nsftl_init_test_category(&test_category[i], temp_test_category_name);

        if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
        {
            report_message = "Test failed due to memory allocation failure";
            nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            for (uint32_t j = 0U; j < i; j++)
            {
                nsftl_destroy_test_category(&test_category[j]);
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

    for (uint32_t i = 0U; i < test::MAX_TEST_CATEGORIES_ARRAY_LENGTH; i++)
    {
        nsftl_destroy_test_category(&test_category[i]);
    }
}

void Test::init_test_unit(nsftl_test_report_t& report)
{
    nsftl_test_unit_t test_unit = nullptr;
    std::string report_message;
    uint32_t status = nsftl_init_test_unit(&test_unit, "Test unit");
    
    if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
    {
        report_message = "Test failed due to memory allocation failure";
        nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
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

void Test::init_multiple_test_units(nsftl_test_report_t& report)
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