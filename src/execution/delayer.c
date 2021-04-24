#include "delayer.h"
#include "fast_rand.h"
#include <stdlib.h> //malloc
// Cross platform sleep
#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h> // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

unsigned int _Delayer_delay_dry(Delayer *delayer) {
  unsigned int rand_int = fast_rand_until(delayer->rand);
  return delayer->min + rand_int;
}

unsigned int Delayer_delay(Delayer *delayer) {
  unsigned int to_wait = _Delayer_delay_dry(delayer);
  cross_platform_sleep(to_wait);
  return to_wait;
}

bool Delayer_is_useless(Delayer *delayer) { return delayer->min + delayer->rand == 0; }

Delayer *Delayer_new(double min, double rand) {
  Delayer *delayer = malloc(sizeof(Delayer));
  Delayer_init(delayer, min, rand);
  return delayer;
}

void Delayer_init(Delayer *to_init, double min, double rand) {
  to_init->min = (unsigned int)(0.5 + min * RATE_LIMIT_UNIT);
  to_init->rand = (unsigned int)(0.5 + rand * RATE_LIMIT_UNIT) + 1; // plus 1 to include the limit
}

int cross_platform_sleep(int to_sleep) {
#ifdef WIN32
  Sleep(to_sleep);
  return 0;
#elif _POSIX_C_SOURCE >= 199309L

  div_t div_out = div(to_sleep, 1000000000);
  struct timespec ts;
  ts.tv_sec = div_out.quot;
  ts.tv_nsec = div_out.rem;
  return nanosleep(&ts, NULL);
#else
  return usleep(to_sleep);
#endif
}
