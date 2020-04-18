#include "executor.h"
#include "argv.h"
#include "munit.h"
#include <stdio.h>
/*A lot of test is done cause stdbuf seem to not work properly and I dont know if FULLY_BUFFERED can be trusted since its not in the tool for some reason, while it's still documented in the library*/

// TODO provide something to test tdbuff is working for an undiviual test see stdbuf test himsef
void test_out() {
  // stdbuf -o 4096 -e L ./child-buf-controle
  char *mode[] = {DEFAULT_BUFFERING, "65536", LINE_BUFFERED};
  char **envp = build_stdbuf_exec_envp(mode);

  char *prompt[] = {"Hello\n", "test\n", "goodbye\n"};
  Output *out = executor_get_output("./child-buf-controle", prompt, 3, envp, 10);
  munit_assert_string_equal(out->out, "stderr 2\nstdout 1\n");
}

void test_out2() {
  // stdbuf -o L -e 4096 ./child-buf-controle DONT PASS (And its weird because it should be equivalent to the shell you see on left, that work perfectely)
  char *mode[] = {DEFAULT_BUFFERING, LINE_BUFFERED, "65536"};
  char **envp = build_stdbuf_exec_envp(mode);

  char *prompt[] = {"Hello\n", "test\n", "goodbye\n"};
  Output *out = executor_get_output("./child-buf-controle", prompt, 3, envp, 10);
  munit_assert_string_equal(out->out, "stdout 1\nstderr 2\n");
}

void test_out3() {
  // Should be stdbuf -o 0 -e L ./child-buf-controle DONT PASS

  char *mode[] = {DEFAULT_BUFFERING, UNBUFFERED, LINE_BUFFERED};
  char **envp = build_stdbuf_exec_envp(mode);

  char *prompt[] = {"Hello\n", "test\n", "goodbye\n"};
  Output *out = executor_get_output("./child-buf-controle", prompt, 3, envp, 10);
  munit_assert_string_equal(out->out, "stdout 1\nstderr 2\n");
}
void test_out4() {
  // stdbuf -o L -e 0 ./child-buf-controle    PASS
  char *mode[] = {DEFAULT_BUFFERING, LINE_BUFFERED, UNBUFFERED};
  char **envp = build_stdbuf_exec_envp(mode);

  char *prompt[] = {"Hello\n", "test\n", "goodbye\n"};
  Output *out = executor_get_output("./child-buf-controle", prompt, 3, envp, 10);
  munit_assert_string_equal(out->out, "stdout 1\nstderr 2\n");
}

int main() {
  /*This test test the prompt feature*/
  char *prompt[] = {"Hello\n", "test\n", "goodbye\n"};
  Output *out = executor_get_output("python3.7 test.py test", prompt, 3, get_envp(), 10);

  FILE *fp = fopen("testfile", "r");
  char buffer[200];

  /* Read and display data */
  size_t size = fread(buffer, 1, 200, fp);
  buffer[size] = 0;
  fclose(fp);
  munit_assert_string_equal(buffer, "test.py test\nHello\ntest\ngoodbye\n");
/* Pyhton dont work with stdbuf, test it on C test (see test_out)
 * https://stackoverflow.com/questions/61250119/stdbuf-no-effect-for-python3-process
 munit_assert_string_equal( out->out, "test sdout recup\ntest stderr recup");
 */

#if LIBSTDBUF_IS_FOUND
  test_out4();
  test_out();
  test_out2();
  test_out3();
#endif
  return 0;
}
