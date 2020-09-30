#include  "fast_rand.h"
#include "stdlib.h"//malloc
#include "rate_limiter.h"
//Cross platform sleep
#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif


unsigned int _Rate_limiter_limit_dry(Rate_limiter* rate_limiter){
	unsigned int rand_int= fast_rand_range(rate_limiter->rand);
	return rate_limiter->min + rand_int;

}
/*Return how much a limiter would wait, internal use*/

unsigned int Rate_limiter_limit(Rate_limiter* rate_limiter){
	unsigned int to_wait=_Rate_limiter_limit_dry(rate_limiter);
	cross_platform_sleep(to_wait);
	return to_wait;

}
/*Wait and return time waited in seconds*/

Rate_limiter* Rate_limiter_new(double min, double rand){
	Rate_limiter* rate_limiter= malloc(sizeof(Rate_limiter));
rate_limiter->min= (unsigned int)(0.5 + min * RATE_LIMIT_UNIT); 
rate_limiter->rand= (unsigned int)(0.5+ rand*RATE_LIMIT_UNIT)+1;//plus 1 to include the limit
}


void cross_platform_sleep(int unity){
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = unity * 1000000;
    nanosleep(&ts, NULL);
#else
    usleep(unity);
#endif
}





