#ifndef __NSFTL_BASE_TYPES_H__
#define __NSFTL_BASE_TYPES_H__

#include <stdint.h>

#if defined(__unix__) || defined(__linux__)
    #include <time.h>
#elif defined(_WIN32) || defined(__WIN32__)
    #include <windows.h>
#elif defined(__APPLE__)
#else
    #error "OS not supported! Unable to continue!"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t nsftl_status_t;
typedef uint32_t nsftl_index_t;
typedef uint32_t nsftl_capacity_t;
#if defined(__unix__) || defined(__linux__)
    typedef struct timespec* nsftl_time_t;
#elif defined(_WIN32) || defined(__WIN32__)
    typedef LARGE_INTEGER* nsftl_time_t;
#elif defined(__APPLE__)
    typedef uint64_t* nsftl_time_t;
#else
    #error "OS not supported! Unable to continue!"
#endif

#ifdef __cplusplus
}
#endif

#endif