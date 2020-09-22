#include "myread.h"
#include "munit.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  char *expected = "import sys\n\nwith open('testfile','w') as f:\n    print(*sys.argv, file=f)\n    print(input(), file=f)\n    print(input(), file=f)\n    print(input(), file=f)\n\nprint(\"test "
                   "sdout recup\")\nprint(\"test stderr recup\", file=sys.stderr)\n";
  size_t max = 1;
  size_t old_max = max;
  char *buff = malloc(sizeof(char) * max);
  

  FILE *fp = fopen("../test_data/targets/prompted.py", "r");

  char buffer[500];
  /* Read and display data */
  size_t size = fread(buffer, 1, 500, fp); // read the file
  buffer[size] = 0;

  int fake_pipe[2];
  pipe(fake_pipe);

  // populate fake pipe (we work on pipe cause real app work on pipes)
  write(fake_pipe[1], buffer, strlen(buffer));
  close(fake_pipe[1]);

  int fd = fake_pipe[0];

  size_t readed = 0;

  size_t oldmax = max;
  read_append(fd, &buff, &readed, &max);

  //I dont know why but if I use munit_assert_size/equal on buff, valgrind report error unexsting error (compilation optimization?)
  munit_assert_string_equal(buff, expected);
  munit_assert_size(strlen(buff), ==, readed);
  fclose(fp);
  return 0;
}
