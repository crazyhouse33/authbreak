#include <eprof.h>
#include <stdio.h>
#include "munit.h"
#include "timer.h"

#pragma weak get_time_ns
unsigned long get_time_ns(){
	static unsigned long res=1;
	return res++;
}

void test_file(){
FILE *fp = fopen("eprof_test", "r");
  char buffer[200];

  /* Read and display data */
  size_t size = fread(buffer, 1, 1000, fp);
  buffer[size] = 0;
  fclose(fp);
  munit_assert_string_equal(buffer, "SFOR,Swhole:1\n");
}

int main(){
	remove("eprof_test");
	FILE* profiler= new_eprof_file("eprof_test");
	eprof_event_start(profiler, FOR, whole);
	for (int i=0;i<5;i++){
		eprof_event_start(profiler,in_for);
		eprof_event_end(profiler,in_for);
	}
	unsigned long t=eprof_event_end(profiler, FOR);
	eprof_event_end_nt(profiler,t, whole);
}
