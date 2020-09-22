#include "output.h"
#include "concat_string.h"
#include "munit.h"
#include <stdio.h>
#include <unistd.h>

int main() {
  char *expected = "import sys\n\nwith open('testfile','w') as f:\n    print(*sys.argv, file=f)\n    print(input(), file=f)\n    print(input(), file=f)\n    print(input(), file=f)\n\nprint(\"test "
                   "sdout recup\")\nprint(\"test stderr recup\", file=sys.stderr)\n";
  size_t expected_size = strlen(expected);

  FILE *fp = fopen("../test_data/targets/prompted.py", "r");

  char buffer[500];
  /* Read and display data */
  size_t size = fread(buffer, 1, 500, fp); // read the file
  buffer[size] = 0;
  fclose(fp);

  int fake_pipe[2];
  pipe(fake_pipe);

  // populate fake pipe
  write(fake_pipe[1], buffer, strlen(buffer));
  close(fake_pipe[1]);
  int fd = fake_pipe[0];
  Output *empty = Output_new();

  char *expected_res = strdup(expected);

  // we are also testing myread but wathever
  size_t new_read = read_append_into_Output(fd, empty);
  munit_assert_size(new_read, ==, expected_size);
  munit_assert_string_equal(expected, empty->out);

  close(fake_pipe[1]);
  close(fd);

  return 0;
}
