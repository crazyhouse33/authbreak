#include "macro_util.h"
#include "stdio.h"
#define EPROF_START_PREPEND(X) S##X
#define EPROF_END_PREPEND(X) E##X

#define EPROF_TO_START_EVENT(...) QUOTE_RES(FOREACH(EPROF_START_PREPEND, (__VA_ARGS__)))
#define EPROF_TO_END_EVENT(...) QUOTE_RES(FOREACH(EPROF_END_PREPEND, (__VA_ARGS__)))

#define eprof_event_end(file, ...) \
__eprof_print_and_time(file, EPROF_TO_END_EVENT(__VA_ARGS__))

#define eprof_event_start(file, ...) \
__eprof_print_and_time(file, EPROF_TO_START_EVENT(__VA_ARGS__))

#define eprof_event_end_nt(profiler, time, ...) \
__eprof_log(profiler, EPROF_TO_END_EVENT(__VA_ARGS__), time)

#define eprof_event_start_nt(profiler, time, ...) \
__eprof_log(profiler, EPROF_TO_START_EVENT(__VA_ARGS__), time)


void __eprof_log(FILE* file, char* string, unsigned long time);
/*Internal function used by macro*/


unsigned long __eprof_print_and_time(FILE* file, char* string);
/*Internal function used by macro*/

FILE* new_eprof_file(char* file_path);
//return FILE pointer to the file_path, can be null if fail (set erno)
