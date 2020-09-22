#include "executor.h"
#include "argv.h"
#include "munit.h"
#include <stdio.h>
/*A lot of test is done cause stdbuf seem to not work properly and I dont know if FULLY_BUFFERED can be trusted since its not in the tool for some reason, while it's still documented in the library*/

// TODO would be better if we craft argv manually for test coupling
void test_out() {
  Output *out = Output_new();
  // stdbuf -o 4096 -e L ./child-buf-controle
  char *mode[] = {DEFAULT_BUFFERING, "65536", LINE_BUFFERED};
  char **envp = build_stdbuf_exec_envp(mode);

  size_t argc;
  char **argv = arg_vector_from_string("./child-buf-controle", &argc);

  char *prompt[] = {"Hello\n", "test\n", "goodbye\n", NULL};
  executor_get_output(argv, prompt, envp, 10, out);
  munit_assert_string_equal(out->out, "stderr 2\nstdout 1\n");
  munit_assert_int(out->exit_status, ==, 78);
}

void test_out2() {

  Output *out = Output_new();
  // stdbuf -o L -e 4096
  char *mode[] = {DEFAULT_BUFFERING, LINE_BUFFERED, "65536"};
  char **envp = build_stdbuf_exec_envp(mode);

  char *prompt[] = {"Hello\n", "test\n", "goodbye\n", NULL};
  size_t argc;
  char **argv = arg_vector_from_string("./child-buf-controle", &argc);

  executor_get_output(argv, prompt, envp, 10,out);
  munit_assert_string_equal(out->out, "stdout 1\nstderr 2\n");
  munit_assert_int(out->exit_status, ==, 78);
}

void test_out3() {
  Output *out = Output_new();
  // Should be stdbuf -o 0 -e L ./child-buf-controle DONT PASS

  char *mode[] = {DEFAULT_BUFFERING, UNBUFFERED, LINE_BUFFERED};
  char **envp = build_stdbuf_exec_envp(mode);
  size_t argc;
  char **argv = arg_vector_from_string("./child-buf-controle", &argc);

  char *prompt[] = {"Hello\n", "test\n", "goodbye\n", NULL};

  executor_get_output(argv, prompt, envp, 10,out );
  munit_assert_string_equal(out->out, "stdout 1\nstderr 2\n");
  munit_assert_int(out->exit_status, ==, 78);
}
void test_out4() {
  Output *out = Output_new();
  // stdbuf -o L -e 0 ./child-buf-controle    PASS
  char *mode[] = {DEFAULT_BUFFERING, LINE_BUFFERED, UNBUFFERED};
  char **envp = build_stdbuf_exec_envp(mode);
  size_t argc;
  char **argv = arg_vector_from_string("./child-buf-controle", &argc);

  char *prompt[] = {"Hello\n", "test\n", "goodbye\n", NULL};
   executor_get_output(argv, prompt, envp, 10,out);
  munit_assert_string_equal(out->out, "stdout 1\nstderr 2\n");
  munit_assert_int(out->exit_status, ==, 78);
}

int main() {
  /*This test test the prompt feature*/
  char *prompt[] = {"Hello\n", "test\n", "goodbye\n", NULL};
  size_t argc;

  char **argv = arg_vector_from_string("/usr/bin/python3 ../test_data/targets/prompted.py test", &argc);

  remove("testfile"); // if we dont remove the file the prompt test is biaised

  Output *out = Output_new();

  executor_get_output(argv, prompt, get_current_envp(), 10,out);

  FILE *fp = fopen("testfile", "r");
  char buffer[200];

  /* Read and display data */
  size_t size = fread(buffer, 1, 200, fp);
  buffer[size] = 0;
  fclose(fp);
  munit_assert_string_equal(buffer, "../test_data/targets/prompted.py test\nHello\ntest\ngoodbye\n");
  munit_assert_int(out->exit_status, ==, 0);
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
