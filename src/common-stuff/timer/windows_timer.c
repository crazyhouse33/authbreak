#if defined(_WIN32)
#include <windows.h>

static LARGE_INTEGER win_frequency;

long get_time_unspecified() {
  LARGE_INTEGER now;
  QueryPerformanceCounter(&now);
  return (unsigned long)now.QuadPart;
}

long get_time_ns() { return (1e9 * get_time_unspecified()) / win_frequency.QuadPart; }

long init_timer() { QueryPerformanceFrequency(win_frequency) return win_frequency.QuadPart; }
#endif
