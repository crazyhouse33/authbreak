#include "commandbuild.h"
#include "munit.h"
void setup() { /*Monkeypatch some functions ( for better isolation and quicker tests suites )*/ }
int main() {
  setup();
        char** prompt={"testprompt", "templatedprompt {}");
        prepare_command_builder("test hey -p {} -u {}", prompt);
        /*Testing internal state*/

        /*Testing normal getCommand*/
        Payload payload = command_builder_next_command();
        munit_assert_string_equal(payload->commandLine, "test hey -p testinject1 -u testinject2") munit_assert_string_equal(payload->prompt[0], "testprompt")
            munit_assert_string_equal(payload->prompt[1], "templatedprompt testinject3")

            /*Testing the fixed one*/
            int *pos = {0, 2};
        char **fix = { "fix1", "fix2" } command_builder_next_command_fixed(pos, fix);

        munit_assert_string_equal(payload->commandLine, "test hey -p fix1 -u testinject3") munit_assert_string_equal(payload->prompt[1], "templatedprompt fix2")

            /*Testing to fix the state*/
            command_builder_fix(pos, fix);
        Payload payload = command_builder_next_command();
        munit_assert_string_equal(payload->commandLine, "test hey -p fix1 -u testinject4") munit_assert_string_equal(payload->prompt[0], "testprompt")
            munit_assert_string_equal(payload->prompt[1], "templatedprompt fix2")

            /*Serializaion test*/
            char *state = command_builder_serialize();
        Payload payload = command_builder_next_command();
        munit_assert_string_equal(payload->commandLine, "test hey -p fix1 -u testinject5") munit_assert_string_equal(payload->prompt[0], "testprompt")
            munit_assert_string_equal(payload->prompt[1], "templatedprompt fix2")

            // Come back to the past
            command_builder_unserialize(char *state);
        Payload payload = command_builder_next_command();
        munit_assert_string_equal(payload->commandLine, "test hey -p fix1 -u testinject5") munit_assert_string_equal(payload->prompt[0], "testprompt")
            munit_assert_string_equal(payload->prompt[1], "templatedprompt fix2")
}
