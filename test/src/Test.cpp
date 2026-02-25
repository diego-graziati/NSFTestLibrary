#include <Test.hpp>
#include <test_subscriber.h>
#include <types/test_category_type.h>
#include <cstring>
#include <defs.hpp>
#include <iostream>

void Test::execute_tests()
{
    mytest_report_type report;
    std::cout << "### TEST:INIT CATEGORY" << std::endl;
    report = Test::init_category();
    print_test_report(report);
    std::cout << "### TEST:SUBSCRIBE SINGLE TEST UNIT" << std::endl;
    report = Test::subscribe_single_test_unit();
    print_test_report(report);
    std::cout << "### TEST:EXECUTE CATEGORY WITH SINGLE UNIT" << std::endl;
    report = Test::execute_category_with_single_unit();
    print_test_report(report);
}

mytest_report_type Test::init_category()
{
    mytest_test_category* test_category = nullptr;
    mytest_init_test_category(&test_category);
    const char* report_message;

    if (test_category == nullptr)
    {
        report_message = "test_category is nullptr";
        mytest_destroy_test_category(test_category);
        return mytest_write_report(report_message, strlen(report_message), test::TEST_FAILED);
    }
    if (test_category->tests == nullptr)
    {
        report_message = "test_category->tests is nullptr";
        mytest_destroy_test_category(test_category);
        return mytest_write_report(report_message, strlen(report_message), test::TEST_FAILED);
    }
    if (test_category->reports == nullptr)
    {
        report_message = "test_category->reports is nullptr";
        mytest_destroy_test_category(test_category);
        return mytest_write_report(report_message, strlen(report_message), test::TEST_FAILED);
    }
    if (test_category->capacity != 10U)
    {
        report_message = "test_category->capacity != 10U";
        mytest_destroy_test_category(test_category);
        return mytest_write_report(report_message, strlen(report_message), test::TEST_FAILED);
    }
    if (test_category->size != 0U)
    {
        report_message = "test_category->size != 0U";
        mytest_destroy_test_category(test_category);
        return mytest_write_report(report_message, strlen(report_message), test::TEST_FAILED);
    }

    mytest_destroy_test_category(test_category);

    report_message = "test succeded";
    return mytest_write_report(report_message, strlen(report_message), test::TEST_SUCCEDED);
}

mytest_report_type Test::subscribe_single_test_unit()
{
    mytest_test_category* test_category = nullptr;
    mytest_init_test_category(&test_category);
    const char* report_message;

    mytest_test_unit test_unit = {
        .test_name = "simple test unit",
        .test_callback_fn = Test::test_callback_fn
    };

    mytest_subscribe_test_unit(test_category, &test_unit);

    if (test_category->size != 1)
    {
        report_message = "test_category->size != 1";
        mytest_destroy_test_category(test_category);
        return mytest_write_report(report_message, strlen(report_message), test::TEST_FAILED);
    }

    if (strcmp(test_category->tests[0].test_name, "simple test unit"))
    {
        report_message = "test_category->tests[0].test_name and \"simple test unit\" aren't equal strings, thus implying the test unit is different";
        mytest_destroy_test_category(test_category);
        return mytest_write_report(report_message, strlen(report_message), test::TEST_FAILED);
    }

    mytest_destroy_test_category(test_category);

    report_message = "test succeded";
    return mytest_write_report(report_message, strlen(report_message), test::TEST_SUCCEDED);
}

mytest_report_type Test::execute_category_with_single_unit()
{
    mytest_test_category* test_category = nullptr;
    mytest_init_test_category(&test_category);
    const char* report_message;

    mytest_test_unit test_unit = {
        .test_name = "simple test unit",
        .test_callback_fn = Test::test_callback_fn
    };

    
    mytest_subscribe_test_unit(test_category, &test_unit);

    mytest_execute_category_tests(test_category);

    if (strcmp(test_category->reports[0].message, "Report test"))
    {
        report_message = "test_category->reports[0].message and \"Report test\" aren't equal strings, thus implying the category execution didn't happen";
        mytest_destroy_test_category(test_category);
        return mytest_write_report(report_message, strlen(report_message), test::TEST_FAILED);
    }

    mytest_destroy_test_category(test_category);

    report_message = "test succeded";
    return mytest_write_report(report_message, strlen(report_message), test::TEST_SUCCEDED);
}

void Test::print_test_report(mytest_report_type& report)
{
    if (report.status == test::TEST_SUCCEDED)
    {
        std::cout << test::ASCII_TERMINAL_GREEN_COLOR << "This test succeded:" << test::ASCII_TERMINAL_RESET << std::endl;
        std::cout << "\t" << report.message << std::endl;
    } 
    else 
    {
        std::cout << test::ASCII_TERMINAL_RED_COLOR << "This test failed:" << test::ASCII_TERMINAL_RESET << std::endl;
        std::cout << "\t" << report.message << std::endl;
    }
}

void Test::test_callback_fn(mytest_report_type* report)
{
    const char* report_message = "Report test";
    (*report) = mytest_write_report(report_message, strlen(report_message), test::TEST_SUCCEDED);
}