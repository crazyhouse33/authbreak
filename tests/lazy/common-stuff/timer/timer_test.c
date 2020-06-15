#include "timer.h"
#include "munit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {

  for (int i = 0; i < 10; i++) {

    FILE *fp;
    char out[1035];

    long res = init_timer();
    long start = get_time_ns();
    long end = start;

    fp = popen("./timer_precision", "r");
    if (fp == NULL) {
      printf("Failed to run command\n");
      exit(1);
    }

    fread(out, sizeof(char), 1035, fp);
    char *space = strchr(out, ' ');
    *space = 0;
    char *placeholder;
    unsigned long start_proc = strtoul(out, &placeholder, 0);
    unsigned long end_proc = strtoul(space + 1, &placeholder, 0);
    munit_assert_ulong(start_proc, >=, start);
    munit_assert_ulong(start_proc, >=, end);
    munit_assert_ulong(end_proc, >=, end);
    munit_assert_ulong(end_proc, >=, start);
    munit_assert_ulong(end_proc, >=, start_proc);

    start = start_proc;
    end = end_proc;

    int ret_status = pclose(fp);
    munit_assert_int(ret_status, ==, 0);
  }
}
