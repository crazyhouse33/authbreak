#include "timer.h"
#include "eprof.h"
#include "stdlib.h"

FILE* new_eprof_file(char* file_path){
	return fopen(file_path, "a");
}



void __eprof_log(FILE* file, char* string, unsigned long time){
fprintf(file, "%s:%lu\n",string,time );
}


unsigned long __eprof_print_and_time(FILE* file, char* string){
	unsigned long time_res=get_time_ns();
	__eprof_log(file, string, time_res);
	return time_res;
}



