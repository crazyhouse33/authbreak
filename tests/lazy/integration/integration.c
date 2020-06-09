#include "munit.h"
#include <stdlib.h>

void generate(char *str, int expected) {

  int res = system(str);
  munit_assert_int(WEXITSTATUS(res), ==, expected);
}

int main() {//the weird quoting is due to system stripping white character at the end, thus we need to add a useless quote to frobid our \n to be erased
  generate("../authbreak \"./basic_auth {GITINCLUDEbasic_auth_crack_user.list} {4:4,charset=rot}\" --prompt \"{GITINCLUDEbasic_auth_crack_pin.list}\n\"", 1);
  return 0;
}
