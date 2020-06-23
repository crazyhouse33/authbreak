// If you are tempted to put that at extern test because it is called by the timer test, dont do because remember extern test dont have access to normal code source
#include "timer.h"
#include "munit.h"
#include "stdio.h"
//TODO check exist
#include "valgrind/valgrind.h"

// popen
#ifdef _Win32
#include <dos.h>
#else
#include <unistd.h>
#endif

// https://stackoverflow.com/questions/1157209/is-there-an-alternative-sleep-function-in-c-to-milliseconds
#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h> // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

static void sleep_ms(int milliseconds) // cross-platform sleep function
{
#ifdef WIN32
  Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
  struct timespec ts;
  ts.tv_sec = milliseconds / 1000;
  ts.tv_nsec = (milliseconds % 1000) * 1000000;
  nanosleep(&ts, NULL);
#else
  usleep(milliseconds * 1000);
#endif
}

#define TIME_TO_SLEEP_MS 30

#define ALLOWED_MISPRESION 3
int main() {
  unsigned long t1 = get_time_ns();
  sleep_ms(TIME_TO_SLEEP_MS);
  unsigned long t2 = get_time_ns();

  // we print in order for an extern test to test that cross process timing is working as well
  printf("%lu %lu", t1, t2);
  unsigned long time = t2 - t1;
  // testing precision
  if (RUNNING_ON_VALGRIND)
	  return 0;
  munit_assert_ulong(time, >=, TIME_TO_SLEEP_MS * NANOS_PER_SEC / 1000);
  munit_assert_ulong(time, <=, (TIME_TO_SLEEP_MS + ALLOWED_MISPRESION) * NANOS_PER_SEC / 1000);
  return 0;
}
