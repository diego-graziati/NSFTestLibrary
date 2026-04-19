#pragma once

#include <types/test_report_type.h>

class Test
{
    public:
        void execute_tests();
        static void test_callback_fn(mytest_report_type_t* report, uint32_t index);
        static void multiple_tests_callback_fn(mytest_report_type_t* report, uint32_t index);
    private:
        /**
         * @author Diego Graziati
         * @brief
         */
        void init_category(mytest_report_type_t& report);
        /**
         * @author Diego Graziati
         * @brief 
         */
        void init_multiple_categories(mytest_report_type_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void init_test_unit(mytest_report_type_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void init_multiple_test_units(mytest_report_type_t& report);
        /**
         * @author Diego Graziati
         * @brief 
         */
        void submit_test_to_single_test_unit(mytest_report_type_t& report);
        /**
         * @author Diego Graziati
         * @brief 
         */
        void submit_test_to_multiple_test_units(mytest_report_type_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void subscribe_single_test_unit(mytest_report_type_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void subscribe_multiple_test_units(mytest_report_type_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void subscribe_single_test_unit_to_multiple_categories(mytest_report_type_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void subscribe_multiple_test_units_to_multiple_categories(mytest_report_type_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void execute_category_with_single_unit(mytest_report_type_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void execute_category_with_multiple_units(mytest_report_type_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void execute_multiple_categories_with_single_unit(mytest_report_type_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void execute_multiple_categories_with_multiple_units(mytest_report_type_t& report);

        void print_test_report(mytest_report_type_t report);
        void destroy_report(mytest_report_type_t& report);
};