#ifdef WIN32
#define RATE_LIMIT_UNIT 1000
#elif _POSIX_C_SOURCE >= 199309L
#define RATE_LIMIT_UNIT 1000000000
#else
#define RATE_LIMIT_UNIT 1000000
#endif

typedef struct Rate_limiter
{
	  unsigned int min;
	  unsigned int rand;
} Rate_limiter;

unsigned int _Rate_limiter_limit_dry(Rate_limiter* Rate_limiter);
/*Return how much a limiter would wait, internal use*/

unsigned int Rate_limiter_limit(Rate_limiter* Rate_limiter);
/*Wait and return time waited in platform specific unit. Multiply by RATE_LIMIT_UNIT to get time in second*/

Rate_limiter* Rate_limiter_new(double min, double rand);
/*Return a limiter so the waiting will always be > min, and the variation will be in range rand. The unit is in seconds*/

void cross_platform_sleep(int unity); 
/*Cross platform sleep fonction, unity may volentarly be different on each platform to let the initialisation phase pay conversion only once.
 *
 * posix>=199309L: nanosecond
 * posix<199309L: microsecond
 * Windows: milisecond
 *
 * Call cross_platform_sleep(n* RATE_LIMIT_UNIT) to sleep n seconds
 * */



