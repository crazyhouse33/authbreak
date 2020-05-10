#include "commandbuild.h"
#include "concat_string.h"
#include "munit.h"
#include <string.h>       //strdup
#include "test_unicity.h" //assert_not_present
void setup() {            /*Monkeypatch some functions ( for better isolation and quicker tests suites )*/
}

char *generate(int firs_ite) {
  // check the concatenation of argvs and prompt
  if (command_builder_next_command())
    return NULL; // We are done if so

  char *res = strdup("");
  int j = 0;
  while (command_builder_argv[j] != NULL) {
    concat_string(&res, command_builder_argv[j++]);
  }
  int p_t = 0;
  while (command_builder_prompt[p_t] != NULL)
    concat_string(&res, command_builder_prompt[p_t++]);

  return res;
}

void test_iteration(char *command, char **prompt, size_t expected_number) { // n is number of template
  prepare_command_builder(command, prompt);
  assert_iteration_test(generate, expected_number);
}
}
int main() {
  setup();
  char *prompt[] = {"testprompt", "templatedprompt {}"};
  char *command = "test hey{} -p tata -u {}";
  test_iteration(command, prompt, 3);
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
