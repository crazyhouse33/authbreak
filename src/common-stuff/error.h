
void critical_error_msg(char* format, ...);
/*Print formated output with paramater appended with CRITICAL ERROR:, call perror, cause abnormal terminaison (leave backtrace for gdb)*/

void controlled_error_msg(int status, char* format,...);
//Same but for error that were expected, do not crash and thus dont leave stack, which is annoying for debuging, but clean if production code.

