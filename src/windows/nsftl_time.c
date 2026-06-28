#include <nsftl_time.h>
#include <miscellaneous/nsftl_test_statuses.h>

/**
 * @brief 
 * @note Since this is the Windows API implementation, nsftl_time_t is the typedef of LARGE_INTEGER*
 * @param clock_time 
 * @return nsftl_status_t 
 */
nsftl_status_t nsftl_getclock_time(nsftl_time_t clock_time)
{
    if (clock_time == NULL)
    {
        return NSFTL_UNABLE_TO_RETRIEVE_CLOCK_TIME;
    }

    if(!QueryPerformanceCounter(clock_time))
    {
        return NSFTL_TEST_REPORT_FAILED_TO_GET_CLOCK_TIME;
    }
    
    return NSFTL_SUCCESS;
}