#ifndef __TEST_UNIT_TYPE_H__
#define __TEST_UNIT_TYPE_H__

#include <types/test_report_type.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mytest_test_unit
{
    const char* test_name;
    void (*test_callback_fn)(mytest_report_type* test_report);
}
mytest_test_unit;

#ifdef __cplusplus
}
#endif

#endif
