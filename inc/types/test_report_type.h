#ifndef __TEST_REPORT_TYPE_H__
#define __TEST_REPORT_TYPE_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mytest_report_type 
{
    const char* message;
    uint32_t status;
}
mytest_report_type;

typedef mytest_report_type* mytest_report_type_t;

#ifdef __cplusplus
}
#endif

#endif