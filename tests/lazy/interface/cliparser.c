#include "cliparser.h"
#include "argv.h"
#include "munit.h"
#include <argp.h> //argp flags
#include <stdio.h>

void test1() {
  // testing public interface
  char *command = "authbreak 'curl -F password=password https://example.com/upload.cgi' --success regexp -s gotprompt -p test --prompt tamere=118";
  size_t argc;
  char **argv = arg_vector_from_string(command, &argc);
  Arguments *args = get_arguments(argc, argv, ARGP_NO_EXIT);
  munit_assert_int(2, ==, args->prompt_cpt);
  munit_assert_int(2, ==, args->sucess_cpt);
  munit_assert_string_equal(args->command_line, "curl -F password=password https://example.com/upload.cgi");
  munit_assert_string_equal(args->prompt[0], "test");
  munit_assert_string_equal(args->prompt[1], "tamere=118");
  munit_assert_string_equal(args->sucess[0], "regexp");
  munit_assert_string_equal(args->sucess[1], "gotprompt");
}

void test2() {
  char *command = "authbreak './basic_auth {GITINCLUDEbasic_auth_crack_user.list} {4:4,charset=rot}' --prompt={GITINCLUDEbasic_auth_crack_pin.list}\n";
  size_t argc;
  char **argv = arg_vector_from_string(command, &argc);
  Arguments *args = get_arguments(argc, argv, ARGP_NO_EXIT);
  munit_assert_int(1, ==, args->prompt_cpt);
  munit_assert_int(0, ==, args->sucess_cpt);
  munit_assert_string_equal(args->command_line, "./basic_auth {GITINCLUDEbasic_auth_crack_user.list} {4:4,charset=rot}");
  munit_assert_string_equal(args->prompt[0], "{GITINCLUDEbasic_auth_crack_pin.list}\n");
}

void test3() {
  char *command = "authbreak './basic_auth {gitincludebasic_auth_crack_user.list} {4:4,charset=rot}' --prompt {gitincludebasic_auth_crack_pin.list}\n";
  size_t argc;
  char **argv = arg_vector_from_string(command, &argc);
  Arguments *args = get_arguments(argc, argv, ARGP_NO_EXIT);
  munit_assert_int(1, ==, args->prompt_cpt);
  munit_assert_int(0, ==, args->sucess_cpt);
  munit_assert_string_equal(args->command_line, "./basic_auth {gitincludebasic_auth_crack_user.list} {4:4,charset=rot}");
  munit_assert_string_equal(args->prompt[0], "{gitincludebasic_auth_crack_pin.list}\n");
}

void test4() {
  char *command = "authbreak './basic_auth {gitincludebasic_auth_crack_user.list} {4:4,charset=rot}' --success !out_eq= --prompt {gitincludebasic_auth_crack_pin.list}\n";
  size_t argc;
  char **argv = arg_vector_from_string(command, &argc);
  Arguments *args = get_arguments(argc, argv, ARGP_NO_EXIT);
  munit_assert_int(1, ==, args->prompt_cpt);
  munit_assert_int(1, ==, args->sucess_cpt);
  munit_assert_string_equal(args->command_line, "./basic_auth {gitincludebasic_auth_crack_user.list} {4:4,charset=rot}");
  munit_assert_string_equal(args->prompt[0], "{gitincludebasic_auth_crack_pin.list}\n");
  munit_assert_string_equal(args->sucess[0], "!out_eq=");
}
int main() {

  test1();
  test2();
  test3();
  test4();

  return 0;
}
