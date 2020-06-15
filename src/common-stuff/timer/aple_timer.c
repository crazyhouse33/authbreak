#if defined(__APPLE__)
#include <mach/mach_time.h>

static mach_timebase_info_data_t info;

unsigned long get_time_unspecified() { return mach_absolute_time(); }

unsigned long get_time_ns() {
  unsigned long now = get_time_unspecified();
  now *= info.numer;
  now /= info.denom;
  return now;
}

/*This must be wrong*/
unsigned long init_timer() {
  mach_timebase_info(&info);
  return info.denom / info.numer;
}
#endif
