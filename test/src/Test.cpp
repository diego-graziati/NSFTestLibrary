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

void Test::execute_tests()
{
    nsftl_report_type_t report = nullptr;
    std::cout << "### TEST:INIT CATEGORY" << std::endl;
    this->init_category(report);
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:INIT MULTIPLE CATEGORIES" << std::endl;
    this->init_multiple_categories(report);
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:INIT TEST UNIT" << std::endl;
    this->init_test_unit(report);
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:INIT MULTIPLE TEST UNITS" << std::endl;
    this->init_multiple_test_units(report);
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:SUBMIT TEST TO SINGLE TEST UNIT" << std::endl;
    this->submit_test_to_single_test_unit(report);
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:SUBMIT TEST TO MULTIPLE TEST UNITS" << std::endl;
    this->submit_test_to_multiple_test_units(report);
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:SUBSCRIBE SINGLE TEST UNIT TO SINGLE TEST CATEGORY" << std::endl;
    this->subscribe_single_test_unit(report);
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:SUBSCRIBE SINGLE TEST UNIT TO MULTIPLE TEST CATEGORIES" << std::endl;
    this->subscribe_single_test_unit_to_multiple_categories(report);
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:SUBSCRIBE MULTIPLE TEST UNITS TO MULTIPLE TEST CATEGORIES" << std::endl;
    this->subscribe_multiple_test_units_to_multiple_categories(report);
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:EXECUTE SINGLE TEST UNIT FROM SINGLE TEST CATEGORY" << std::endl;
    this->execute_category_with_single_unit(report);
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:SUBSCRIBE MULTIPLE TEST UNITS TO SINGLE TEST CATEGORY" << std::endl;
    this->subscribe_multiple_test_units(report);
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:EXECUTE MULTIPLE TEST UNITS FROM SINGLE TEST CATEGORY" << std::endl;
    this->execute_category_with_multiple_units(report);
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:EXECUTE SINGLE TEST UNIT FROM MULTIPLE TEST CATEGORIES" << std::endl;
    this->execute_multiple_categories_with_single_unit(report);
    this->print_test_report(report);
    this->destroy_report(report);

    std::cout << "### TEST:EXECUTE MULTIPLE TEST UNITS FROM MULTIPLE TEST CATEGORIES" << std::endl;
    this->execute_multiple_categories_with_multiple_units(report);
    this->print_test_report(report);
    this->destroy_report(report);
}

void Test::print_test_report(nsftl_report_type_t report)
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

void Test::destroy_report(nsftl_report_type_t& report)
{
    mynsftl_test_destroy_test_report(&report);
    report = nullptr;
}

void Test::test_callback_fn(nsftl_report_type_t* report, uint32_t index)
{
    std::string report_message = "Report test";
    mytest_write_report(report, report_message.c_str(), report_message.length(), test::TEST_SUCCEDED);
}

void Test::multiple_tests_callback_fn(nsftl_report_type_t* report, uint32_t index)
{
    char report_message[NSFTL_TEST_REPORT_MAX_MESSAGE_LENGTH] = {0};
    std::snprintf(report_message, std::string("Report of test n°: ").length() + 2, "Report of test n°: %u", index);
    mytest_write_report(report, report_message, std::string(report_message).length(), test::TEST_SUCCEDED);
}