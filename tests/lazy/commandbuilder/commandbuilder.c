#include "commandbuild.h"
#include "concat_string.h"
#include "munit.h"
#include "string.h" //strdup
void setup() {      /*Monkeypatch some functions ( for better isolation and quicker tests suites )*/
}

void assert_not_present(char *string, char **result, size_t size_res) {
  while (size_res-- >= 0)
    munit_assert_string_not_equal(result[size_res], string);
}

void test_iteration(char *command, char **prompt, size_t n) { // n is number of template
  size_t expected_number = n * (n + 1) / 2;
  prepare_command_builder(command, prompt);
  /*Check that we iterate once only on everythings*/
  char **result_table = malloc(sizeof(char *) * expected_number);
  for (int i = 0; i < expected_number; i++) {
    result_table[i] = strdup("");
  }

  for (size_t i = 0; i < expected_number; i++) {
    command_builder_next_command();
    int j = 0;

    while (command_builder_argv[j] != NULL) {
      concat_string(&result_table[j], command_builder_argv[j++]);
    }
    int p_t = 0;
    while (command_builder_prompt[p_t] != NULL)
      concat_string(&result_table[j], command_builder_prompt[p_t++]);

    assert_not_present(result_table[j], result_table, j); // compare with previous ones
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
