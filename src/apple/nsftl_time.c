#include <nsftl_time.h>
#include <miscellaneous/nsftl_test_statuses.h>

/**
 * @brief 
 * @note Since this is the POSIX API implementation, nsftl_time_t is the typedef of uint64_t*
 * @param clock_time 
 * @return nsftl_status_t 
 */
nsftl_status_t nsftl_getclock_time(nsftl_time_t clock_time)
{
    if (clock_time == NULL)
    {
        return NSFTL_UNABLE_TO_RETRIEVE_CLOCK_TIME;
    }

    uint64_t actual_time = clock_gettime_nsec_np(CLOCK_UPTIME_RAW);

    if(actual_time == 0)
    {
        return NSFTL_TEST_REPORT_FAILED_TO_GET_CLOCK_TIME;
    }

    *clock_time = actual_time;

    return NSFTL_SUCCESS;
}