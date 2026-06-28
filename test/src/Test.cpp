#include <Test.hpp>
#include <nsftl_test_subscriber.h>
#include <nsftl_test_init.h>
#include <nsftl_test_execute.h>
#include <nsftl_test_destroy.h>
#include <nsftl_test_utils.h>
#include <types/nsftl_test_category_type.h>
#include <miscellaneous/nsftl_test_statuses.h>
#include <defs.hpp>
#include <iostream>
#include <ctime>

void Test::execute_tests()
{
    this->init_tests_collection();
    this->submit_tests_collection();
    this->subscribe_tests_collection();
    this->execute_tests_collection();
}

void Test::print_test_report(nsftl_test_report_t report)
{
    if (report == NULL || report->message == NULL)
    {
        std::cout << "\tUnable to read null" << std::endl;
        return;
    }

    if (report->status == test::TEST_SUCCEDED)
    {
        std::cout << test::ASCII_TERMINAL_RESET << "\t" << test::ASCII_TERMINAL_GREEN_COLOR << report->message << test::ASCII_TERMINAL_RESET << std::endl;
    }
    else if (report->status == test::TEST_FAILED)
    {
        std::cout << test::ASCII_TERMINAL_RESET << "\t" << test::ASCII_TERMINAL_RED_COLOR << report->message << test::ASCII_TERMINAL_RESET << std::endl;
    }
    else
    {
        std::cout << "\t" << report->message << std::endl;
    }
}

nsftl_status_t Test::init_report(nsftl_test_report_t& report)
{
    if (report != NULL)
    {
        this->destroy_report(report);
    }
    
    return nsftl_init_test_report(&report);
}

void Test::start_report_timer(nsftl_test_report_t& report)
{
    nsftl_start_report_timer(report);
}

void Test::stop_report_timer(nsftl_test_report_t& report)
{
    nsftl_stop_report_timer(report);
}

void Test::destroy_report(nsftl_test_report_t& report)
{
    nsftl_destroy_test_report(&report);
    report = nullptr;
}

void Test::test_callback_fn(nsftl_test_report_t* report, nsftl_index_t index)
{
    std::string report_message = "Report test";
    nsftl_write_report(report, report_message.c_str(), report_message.length(), test::TEST_SUCCEDED);
}

void Test::multiple_tests_callback_fn(nsftl_test_report_t* report, nsftl_index_t index)
{
    char report_message[NSFTL_TEST_REPORT_MAX_MESSAGE_LENGTH] = {0};
    std::snprintf(report_message, std::string("Report of test n°: ").length() + 2, "Report of test n°: %u", index);
    nsftl_write_report(report, report_message, std::string(report_message).length(), test::TEST_SUCCEDED);
}