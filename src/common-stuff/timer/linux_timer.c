#if defined(linux) || defined(__linux__) || defined(__linux) || defined(__gnu_linux__)

#include "timer.h"
#include <time.h>
#ifdef CLOCK_MONOTONIC
#define CLOCKID CLOCK_MONOTONIC
#else
#define CLOCKID CLOCK_REALTIME
#endif

unsigned long get_time_ns() {

  long now;
  struct timespec spec;
  clock_gettime(CLOCKID, &spec);
  now = spec.tv_sec * NANOS_PER_SEC + spec.tv_nsec;
  return now;
}

unsigned long get_time_unspecified() { return get_time_ns(); }

unsigned long init_timer() {

  struct timespec linux_time;
  clock_getres(CLOCKID, &linux_time);
  return linux_time.tv_sec * NANOS_PER_SEC + linux_time.tv_nsec;
}
#endif
