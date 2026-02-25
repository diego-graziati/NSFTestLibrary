#pragma once

#include <types/test_report_type.h>

class Test
{
    public:
        void execute_tests();
    private:
        mytest_report_type init_category();
        mytest_report_type subscribe_single_test_unit();
        mytest_report_type execute_category_with_single_unit();

        void print_test_report(mytest_report_type& report);
        static void test_callback_fn(mytest_report_type* report);
};