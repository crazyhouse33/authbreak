#include "output.h"
#include "concat_string.h"
#include "munit.h"
#include <stdio.h>
#include <unistd.h>

int main() {
  char *expected = "import sys\n\nwith open('testfile','w') as f:\n    print(*sys.argv, file=f)\n    print(input(), file=f)\n    print(input(), file=f)\n    print(input(), file=f)\n\nprint(\"test "
                   "sdout recup\")\nprint(\"test stderr recup\", file=sys.stderr)\n";
  size_t expected_size = strlen(expected);

  FILE *fp = fopen("test.py", "r");

  char buffer[500];
  /* Read and display data */
  size_t size = fread(buffer, 1, 500, fp); // read the file
  buffer[size] = 0;
  fclose(fp);

  int fake_pipe[2];
  pipe(fake_pipe);

  // populate fake pipe
  write(fake_pipe[1], buffer, strlen(buffer));
  int fd = fake_pipe[0];
  Output *empty = Output_new();
  size_t readed = 0;

  char *expected_res = strdup(expected);

  // we are also testing myread but wathever
  size_t new_read = read_append_into_Output(fd, empty, &readed);
  munit_assert_size(readed, ==, expected_size);
  munit_assert_size(new_read, ==, expected_size);
  empty->out[readed] = 0;
  munit_assert_string_equal(expected, empty->out);
  empty->out[readed] = 18;

  for (int cpt = 2; cpt < 8; cpt++) {
    expected_res = get_concatenation_string(expected_res, expected);
    write(fake_pipe[1], buffer, strlen(buffer));
    new_read = read_append_into_Output(fd, empty, &readed);
    munit_assert_size(new_read, ==, expected_size);
    munit_assert_size(readed, ==, cpt * expected_size);

    empty->out[readed] = 0;
    munit_assert_string_equal(expected_res, empty->out);
    empty->out[readed] = 18;
  }
  close(fake_pipe[1]);
  close(fd);

  return 0;
}
