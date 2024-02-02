
#ifndef __TIME_UTILS_HPP__
#define __TIME_UTILS_HPP__

#include <stdint.h>
#include <time.h>

#define NSEC_PER_SEC 1000000000
#define USEC_PER_SEC 1000000
#define MSEC_PER_SEC 1000

namespace time_utils
{
    inline bool cmp(const timespec *t1, const timespec *t2)
    {
        if (t1->tv_sec > t2->tv_sec)
            return true;
        else if (t1->tv_sec < t2->tv_sec)
            return false;
        else
            return t1->tv_nsec > t2->tv_nsec;
    }

    inline void normalize(timespec *t)
    {
        while (t->tv_nsec >= NSEC_PER_SEC)
        {
            t->tv_sec += 1;
            t->tv_nsec -= NSEC_PER_SEC;
        }
    }

    inline void sub(timespec *t1, timespec *t2, timespec *res)
    {   
        if(cmp(t1,t2))
        {
            std::runtime_error("time order error! t1 > t2");
        }
        
        res->tv_sec = t1->tv_sec - t2->tv_sec;
        res->tv_nsec = t1->tv_nsec - t2->tv_nsec;

        normalize(res);
    }

    inline uint64_t to_nsec(const timespec *t)
    {
        return static_cast<uint64_t>(t->tv_sec) * NSEC_PER_SEC + static_cast<uint64_t>(t->tv_nsec);
    }

}
#endif
