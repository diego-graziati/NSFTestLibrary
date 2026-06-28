#include <Test.hpp>
#include <nsftl_test_subscriber.h>
#include <nsftl_test_init.h>
#include <nsftl_test_destroy.h>
#include <nsftl_test_utils.h>
#include <types/nsftl_test_category_type.h>
#include <miscellaneous/nsftl_test_statuses.h>
#include <defs.hpp>
#include <string>
#include <iostream>
#include <cstdio>

void Test::subscribe_tests_collection()
{
    nsftl_test_report_t report = nullptr;

    std::cout << "### TEST:SUBSCRIBE SINGLE TEST UNIT TO SINGLE TEST CATEGORY" << std::endl;
    if(this->init_report(report) == NSFTL_SUCCESS)
    {
        this->start_report_timer(report);
        this->subscribe_single_test_unit(report);
        this->stop_report_timer(report);
    }
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:SUBSCRIBE SINGLE TEST UNIT TO MULTIPLE TEST CATEGORIES" << std::endl;
    if(this->init_report(report) == NSFTL_SUCCESS)
    {
        this->start_report_timer(report);
        this->subscribe_single_test_unit_to_multiple_categories(report);
        this->stop_report_timer(report);
    }
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:SUBSCRIBE MULTIPLE TEST UNITS TO MULTIPLE TEST CATEGORIES" << std::endl;
    if(this->init_report(report) == NSFTL_SUCCESS)
    {
        this->start_report_timer(report);
        this->subscribe_multiple_test_units_to_multiple_categories(report);
        this->stop_report_timer(report);
    }
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:SUBSCRIBE MULTIPLE TEST UNITS TO SINGLE TEST CATEGORY" << std::endl;
    if(this->init_report(report) == NSFTL_SUCCESS)
    {
        this->start_report_timer(report);
        this->subscribe_multiple_test_units(report);
        this->stop_report_timer(report);
    }
    this->print_test_report(report);
    this->destroy_report(report);
}

void Test::subscribe_single_test_unit(nsftl_test_report_t& report)
{
    nsftl_test_category_t test_category = nullptr;
    std::string report_message;
    uint32_t status = nsftl_init_test_category(&test_category, "Test category");

    if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
    {
        report_message = "Test failed due to memory allocation failure during test_category initialization";
        nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        return;
    }

    nsftl_test_unit_t test_unit = nullptr;
    status = nsftl_init_test_unit(&test_unit, "Test unit");
    if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
    {
        report_message = "Test failed due to memory allocation failure during test_unit initialization";
        nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        nsftl_destroy_test_category(&test_category);
        return;
    }

    status = nsftl_submit_test_to_test_unit(test_unit, Test::test_callback_fn);

    if (status == NSFTL_UNABLE_TO_SUBMIT_TEST_FUNCTION_TO_TEST_UNIT)
    {
        report_message = "Test failed due to inability to submit the test function to the test unit";
        nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        nsftl_destroy_test_category(&test_category);
        nsftl_destroy_test_unit(&test_unit);
        return;
    }

    status = nsftl_subscribe_test_unit(test_category, &test_unit);

    if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
    {
        report_message = "Test failed due to memory allocation failure during the test_unit subscription to the test_category";
        nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        nsftl_destroy_test_category(&test_category);
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

    nsftl_destroy_test_category(&test_category);
}

void Test::subscribe_multiple_test_units(nsftl_test_report_t& report)
{
    nsftl_test_category_t test_category = nullptr;
    std::string report_message;
    uint32_t status = nsftl_init_test_category(&test_category, "Test category");

    if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
    {
        report_message = "Test failed due to memory allocation failure during test_category initialization";
        nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
        return;
    }

    nsftl_test_unit_t test_unit = nullptr;
    for (uint32_t i = 0U; i < 30; i++)
    {
        char temp_test_unit_name[NSFTL_TEST_UNIT_MAX_NAME_LENGTH] = {0};
        std::snprintf(temp_test_unit_name, std::string("Test Unit n°: ").length() + 2, "Test Unit n°: %u", i);
        status = nsftl_init_test_unit(&test_unit, temp_test_unit_name);
        if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
        {
            report_message = "Test failed due to memory allocation failure during test_unit initialization";
            nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            nsftl_destroy_test_category(&test_category);
            return;
        }

        status = nsftl_submit_test_to_test_unit(test_unit, Test::multiple_tests_callback_fn);

        if (status == NSFTL_UNABLE_TO_SUBMIT_TEST_FUNCTION_TO_TEST_UNIT)
        {
            report_message = "Test failed due to inability to submit the test function to the test unit";
            nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            nsftl_destroy_test_category(&test_category);
            nsftl_destroy_test_unit(&test_unit);
            return;
        }

        status = nsftl_subscribe_test_unit(test_category, &test_unit);

        if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
        {
            report_message = "Test failed due to memory allocation failure during the test_unit subscription to the test_category";
            nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            nsftl_destroy_test_category(&test_category);
            nsftl_destroy_test_unit(&test_unit);
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

    nsftl_destroy_test_category(&test_category);
}

void Test::subscribe_single_test_unit_to_multiple_categories(nsftl_test_report_t& report)
{
    nsftl_test_category_t test_category[test::MAX_TEST_CATEGORIES_ARRAY_LENGTH] = {0};
    nsftl_test_unit_t test_unit = nullptr;
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

        nsftl_init_test_unit(&test_unit, "Test unit");
    
        if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
        {
            report_message = "Test failed due to memory allocation failure during test_unit initialization";
            nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            for (uint32_t j = 0U; j <= i; j++)
            {
                nsftl_destroy_test_category(&test_category[j]);
            }
            return;
        }

        status = nsftl_submit_test_to_test_unit(test_unit, Test::test_callback_fn);

        if (status == NSFTL_UNABLE_TO_SUBMIT_TEST_FUNCTION_TO_TEST_UNIT)
        {
            report_message = "Test failed due to inability to submit the test function to the test unit";
            nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            nsftl_destroy_test_unit(&test_unit);
            for (uint32_t j = 0U; j <= i; j++)
            {
                nsftl_destroy_test_category(&test_category[j]);
            }
            return;
        }

        status = nsftl_subscribe_test_unit(test_category[i], &test_unit);

        if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
        {
            report_message = "Test failed due to memory allocation failure";
            nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
            nsftl_destroy_test_unit(&test_unit);
            for (uint32_t j = 0U; j <= i; j++)
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

void Test::subscribe_multiple_test_units_to_multiple_categories(nsftl_test_report_t& report)
{
    nsftl_test_category_t test_category[test::MAX_TEST_CATEGORIES_ARRAY_LENGTH] = {0};
    std::string report_message;
    uint32_t status = NSFTL_SUCCESS;

    for (uint32_t i = 0U; i < test::MAX_TEST_CATEGORIES_ARRAY_LENGTH; i++)
    {
        nsftl_test_unit_t test_unit[test::MAX_TEST_CATEGORIES_ARRAY_LENGTH] = {0};
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

        for (uint32_t j = 0U; j < test::MAX_TEST_UNITS_ARRAY_LENGTH; j++)
        {
            char temp_test_unit_name[NSFTL_TEST_UNIT_MAX_NAME_LENGTH] = {0};
            std::snprintf(temp_test_unit_name, std::string("Test Unit n°: ").length() + 2, "Test Unit n°: %u", i);
            status = nsftl_init_test_unit(&test_unit[j], temp_test_unit_name);
        
            if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
            {
                report_message = "Test failed due to memory allocation failure";
                nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
                for (uint32_t k = 0U; k < j; k++)
                {
                    nsftl_destroy_test_unit(&test_unit[k]);
                }
                for (uint32_t k = 0U; k <= i; k++)
                {
                    nsftl_destroy_test_category(&test_category[k]);
                }
                return;
            }

            status = nsftl_submit_test_to_test_unit(test_unit[j], Test::test_callback_fn);

            if (status == NSFTL_UNABLE_TO_SUBMIT_TEST_FUNCTION_TO_TEST_UNIT)
            {
                report_message = "Test failed due to inability to submit the test function to the test unit";
                nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
                for (uint32_t k = 0U; k <= j; k++)
                {
                    nsftl_destroy_test_unit(&test_unit[k]);
                }
                for (uint32_t k = 0U; k <= i; k++)
                {
                    nsftl_destroy_test_category(&test_category[k]);
                }
                return;
            }

            status = nsftl_subscribe_test_unit(test_category[i], &test_unit[j]);

            if (status == NSFTL_MEMORY_ALLOCATION_FAILED_MEMORY_INSUFFICIENT)
            {
                report_message = "Test failed due to memory allocation failure during test unit subscription to test category";
                nsftl_write_report(&report, report_message.c_str(), report_message.length(), test::TEST_FAILED);
                for (uint32_t k = 0U; k <= j; k++)
                {
                    nsftl_destroy_test_unit(&test_unit[k]);
                }
                for (uint32_t k = 0U; k <= i; k++)
                {
                    nsftl_destroy_test_category(&test_category[k]);
                }
                return;
            }
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