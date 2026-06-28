#pragma once

#include <types/nsftl_test_report_type.h>

class Test
{
    public:
        void execute_tests();
        static void test_callback_fn(nsftl_test_report_t* report, nsftl_index_t index);
        static void multiple_tests_callback_fn(nsftl_test_report_t* report, nsftl_index_t index);
    private:

        void init_tests_collection();
        void submit_tests_collection();
        void execute_tests_collection();
        void subscribe_tests_collection();

        /**
         * @author Diego Graziati
         * @brief
         */
        void init_category(nsftl_test_report_t& report);
        /**
         * @author Diego Graziati
         * @brief 
         */
        void init_multiple_categories(nsftl_test_report_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void init_test_unit(nsftl_test_report_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void init_multiple_test_units(nsftl_test_report_t& report);
        /**
         * @author Diego Graziati
         * @brief 
         */
        void submit_test_to_single_test_unit(nsftl_test_report_t& report);
        /**
         * @author Diego Graziati
         * @brief 
         */
        void submit_test_to_multiple_test_units(nsftl_test_report_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void subscribe_single_test_unit(nsftl_test_report_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void subscribe_multiple_test_units(nsftl_test_report_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void subscribe_single_test_unit_to_multiple_categories(nsftl_test_report_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void subscribe_multiple_test_units_to_multiple_categories(nsftl_test_report_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void execute_category_with_single_unit(nsftl_test_report_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void execute_category_with_multiple_units(nsftl_test_report_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void execute_multiple_categories_with_single_unit(nsftl_test_report_t& report);
        /**
         * @author Diego Graziati
         * @brief
         */
        void execute_multiple_categories_with_multiple_units(nsftl_test_report_t& report);

        void print_test_report(nsftl_test_report_t report);
        nsftl_status_t init_report(nsftl_test_report_t& report);
        void start_report_timer(nsftl_test_report_t& report);
        void stop_report_timer(nsftl_test_report_t& report);
        void destroy_report(nsftl_test_report_t& report);
};