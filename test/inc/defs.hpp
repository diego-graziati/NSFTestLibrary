#pragma once

#include <stdint.h>

namespace test
{
    inline constexpr uint32_t TEST_SUCCEDED = 0U;
    inline constexpr uint32_t TEST_FAILED = 1U;
    inline constexpr uint32_t MAX_TEST_UNITS_ARRAY_LENGTH = 30U;
    inline constexpr uint32_t MAX_TEST_CATEGORIES_ARRAY_LENGTH = test::MAX_TEST_UNITS_ARRAY_LENGTH;

    inline constexpr const char* ASCII_TERMINAL_RED_COLOR = "\x1b[1;31m";
    inline constexpr const char* ASCII_TERMINAL_GREEN_COLOR = "\x1b[0;32m";
    inline constexpr const char* ASCII_TERMINAL_RESET = "\x1b[0m";
};