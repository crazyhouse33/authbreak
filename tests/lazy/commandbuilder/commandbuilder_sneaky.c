#include "commandbuild_sneaky.h"
#include "concat_string.h"
#include "default_options.h"
#include "munit.h"
#include "test_unicity.h" //assert_not_present
#include <string.h>       //strdup

static Sneaky_command_builder* builder;

char *generate(int firs_ite) {
  if (!firs_ite)
    if (sneaky_command_builder_next_command(builder))
      return NULL;
  // check the concatenation of argvs and prompt

  char *res = strdup("");
  int j = 0;
  while (builder->builder.argv[j] != NULL) {
    concat_string(&res, builder->builder.argv[j++]);
  }
  int p_t = 0;
  while (builder->builder.prompts[p_t] != NULL)
    concat_string(&res, builder->builder.prompts[p_t++]);

  return res;
}

void test_iteration(char *command, char **prompt, size_t expected_number) { // n is number of template
  builder=sneaky_command_builder_new(command, prompt);
  assert_iteration_test(generate, expected_number);
}

int main() {
  DEFAULT_CHARSET = strdup("01");
  DEFAULT_LEN_MIN = 0;
  DEFAULT_LEN_MAX = 2;
  DEFAULT_SEPARATOR = '\n';
  char *prompt[] = {strdup("testprompt"), strdup("templatedprompt --{}--"), NULL};
  char *command = strdup("test hey--{}-- -p tata -u --{}--");
  // each handler have 1 + 2 + 4 7
  test_iteration(command, prompt, 7 * 7 * 7);
}

/*Testing internal state*/

//       /*Testing normal getCommand*/
//
//       Payload payload = command_builder_next_command();
//       munit_assert_string_equal(payload->commandLine, "test hey -p testinject1 -u testinject2") munit_assert_string_equal(payload->prompt[0], "testprompt")
//           munit_assert_string_equal(payload->prompt[1], "templatedprompt testinject3")

//           /*Testing the fixed one*/
//           int *pos = {0, 2};
//       char **fix = { "fix1", "fix2" } command_builder_next_command_fixed(pos, fix);

//       munit_assert_string_equal(payload->commandLine, "test hey -p fix1 -u testinject3") munit_assert_string_equal(payload->prompt[1], "templatedprompt fix2")

//           /*Testing to fix the state*/
//           command_builder_fix(pos, fix);
//       Payload payload = command_builder_next_command();
//       munit_assert_string_equal(payload->commandLine, "test hey -p fix1 -u testinject4") munit_assert_string_equal(payload->prompt[0], "testprompt")
//           munit_assert_string_equal(payload->prompt[1], "templatedprompt fix2")

//           /*Serializaion test*/
//           char *state = command_builder_serialize();
//       Payload payload = command_builder_next_command();
//       munit_assert_string_equal(payload->commandLine, "test hey -p fix1 -u testinject5") munit_assert_string_equal(payload->prompt[0], "testprompt")
//           munit_assert_string_equal(payload->prompt[1], "templatedprompt fix2")

//           // Come back to the past
//           command_builder_unserialize(char *state);
//       Payload payload = command_builder_next_command();
//       munit_assert_string_equal(payload->commandLine, "test hey -p fix1 -u testinject5") munit_assert_string_equal(payload->prompt[0], "testprompt")
//           munit_assert_string_equal(payload->prompt[1], "templatedprompt fix2")
//
