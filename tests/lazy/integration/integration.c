#include "munit.h"
#include <stdlib.h>

void generate(char *str, int expected) {

  int res = system(str);
  munit_assert_int(WEXITSTATUS(res), ==, expected);
}

int main() { // the weird quoting is due to system stripping white character at the end, thus we need to add a useless quote to frobid our \n to be erased

  generate("../authbreak \"./basic_auth {../test_data/list/basic_auth_crack_user.list} {2:2,charset=or}\" --prompt \"{../test_data/list/basic_auth_crack_pin.list}\n\"", 1);
  generate("../authbreak \"./basic_auth {../test_data/list/basic_auth_crack_user.list} {2:2,charset=or}\" --prompt \"{../test_data/list/basic_auth_crack_pin.list}\n\" --success \"out_eq=Starting "
           "main\nHi admin, "
           "what's the secret pin?\"",
           0);

  return 0;
}
