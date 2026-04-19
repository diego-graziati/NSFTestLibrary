#ifndef __NSFTL_TEST_REPORT_TYPE_H__
#define __NSFTL_TEST_REPORT_TYPE_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nsftl_report_type 
{
    const char* message;
    uint32_t status;
}
nsftl_report_type;

typedef nsftl_report_type* nsftl_report_type_t;

#ifdef __cplusplus
}
#endif

#endif