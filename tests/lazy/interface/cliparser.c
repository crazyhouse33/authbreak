#include "cliparser.h"
#include "argv.h"
#include "default_options.h"
#include "munit.h"
#include "null_vec.h"
#include <argp.h> //argp flags
#include <stdio.h>

size_t get_size_composed(Composed_classifier *class) { return class->num_status_eq + class->num_status_diff + class->num_stringcmp + class->num_time; }

void test1() {
  // testing public interface
  char *command = "authbreak 'curl -F password=password https://example.com/upload.cgi' --success out_eq=18 -s out_eq!=5 -p test --prompt tamere=118 --wait 1 --random-wait 16";
  size_t argc;
  char **argv = arg_vector_from_string(command, &argc);
  Arguments *args = get_arguments(argc, argv, ARGP_NO_EXIT);

  munit_assert_size(2, ==, get_vector_count((void **)args->prompt));
  munit_assert_size(2, ==, get_size_composed(&args->classifier_combined->groups[0]));
  munit_assert_string_equal(args->command_line, "curl -F password=password https://example.com/upload.cgi");
  munit_assert_string_equal(args->prompt[0], "test");
  munit_assert_string_equal(args->prompt[1], "tamere=118");
  munit_assert_string_equal(args->classifier_combined->groups[0].stringcmp_class[0].target_string, "18");
  munit_assert_string_equal(args->classifier_combined->groups[0].stringcmp_class[1].target_string, "5");
  munit_assert_double(args->wait, ==, 1);
  munit_assert_double(args->random_wait, ==, 16);
}

void test2() {
  char *command = "authbreak './basic_auth {../test_data/list/basic_auth_crack_user.list} {4:4,charset=rot}' --prompt={../test_data/list/basic_auth_crack_pin.list}\n";
  size_t argc;
  char **argv = arg_vector_from_string(command, &argc);
  Arguments *args = get_arguments(argc, argv, ARGP_NO_EXIT);
  munit_assert_int(1, ==, get_vector_count((void **)args->prompt));
  munit_assert_int(0, ==, args->classifier_combined->num_groups);
  munit_assert_string_equal(args->command_line, "./basic_auth {../test_data/list/basic_auth_crack_user.list} {4:4,charset=rot}");
  munit_assert_string_equal(args->prompt[0], "{../test_data/list/basic_auth_crack_pin.list}\n");
  munit_assert_double(args->wait, ==, 0);
  munit_assert_double(args->random_wait, ==, 0);
}

void test3() {
  char *command = "authbreak './basic_auth {../test_data/list/basic_auth_crack_user.list} {4:4,charset=rot}' --prompt {../test_data/list/basic_auth_crack_pin.list}\n";
  size_t argc;
  char **argv = arg_vector_from_string(command, &argc);
  Arguments *args = get_arguments(argc, argv, ARGP_NO_EXIT);
  munit_assert_int(1, ==, get_vector_count((void **)args->prompt));
  munit_assert_int(0, ==, args->classifier_combined->num_groups);
  munit_assert_string_equal(args->command_line, "./basic_auth {../test_data/list/basic_auth_crack_user.list} {4:4,charset=rot}");
  munit_assert_string_equal(args->prompt[0], "{../test_data/list/basic_auth_crack_pin.list}\n");
}

void test4() {
  char *command = "authbreak './basic_auth {../test_data/list/basic_auth_crack_user.list} {4:4,charset=rot}' --success !out_eq= --prompt {../test_data/list/basic_auth_crack_pin.list}\n";
  size_t argc;
  char **argv = arg_vector_from_string(command, &argc);
  Arguments *args = get_arguments(argc, argv, ARGP_NO_EXIT);
  munit_assert_int(1, ==, get_vector_count((void **)args->prompt));
  munit_assert_int(1, ==, args->classifier_combined->num_groups);
  munit_assert_int(1, ==, args->classifier_combined->groups[0].num_stringcmp);
  munit_assert_string_equal(args->command_line, "./basic_auth {../test_data/list/basic_auth_crack_user.list} {4:4,charset=rot}");
  munit_assert_string_equal(args->prompt[0], "{../test_data/list/basic_auth_crack_pin.list}\n");
  munit_assert_string_equal(args->classifier_combined->groups[0].stringcmp_class[0].target_string, "");
}

void test_OR_and_NOT() {
  char *command = "authbreak './basic_auth {../test_data/list/basic_auth_crack_user.list} {4:4,charset=rot}' --success !out_eq=ho --prompt {../test_data/list/basic_auth_crack_pin.list}\n --OR "
                  "--success= time<45 --OR --NOT --sucess status>=20 --sucess out_eq!=89 --sucess status>=10";
  size_t argc;
  char **argv = arg_vector_from_string(command, &argc);
  Arguments *args = get_arguments(argc, argv, ARGP_NO_EXIT);
  munit_assert_int(1, ==, get_vector_count((void **)args->prompt));
  munit_assert_int(3, ==, args->classifier_combined->num_groups);
  munit_assert_int(1, ==, args->classifier_combined->groups[0].num_stringcmp);
  munit_assert_int(0, ==, args->classifier_combined->groups[0].num_time);
  munit_assert_int(0, ==, args->classifier_combined->groups[0].num_status_eq);
  munit_assert_int(0, ==, args->classifier_combined->groups[0].num_status_diff);

  munit_assert_int(0, ==, args->classifier_combined->groups[1].num_stringcmp);
  munit_assert_int(1, ==, args->classifier_combined->groups[1].num_time);
  munit_assert_int(0, ==, args->classifier_combined->groups[1].num_status_eq);
  munit_assert_int(0, ==, args->classifier_combined->groups[1].num_status_diff);

  munit_assert_int(1, ==, args->classifier_combined->groups[2].num_stringcmp);
  munit_assert_int(0, ==, args->classifier_combined->groups[2].num_time);
  munit_assert_int(0, ==, args->classifier_combined->groups[2].num_status_eq);
  munit_assert_int(2, ==, args->classifier_combined->groups[2].num_status_diff);
}

void test_default() {
  char *command = "authbreak './basic_auth {../test_data/list/basic_auth_crack_user.list} {4:4,charset=rot}' --default-len-max 48 --default-charset koi --default-separator 7 --success !out_eq= "
                  "--prompt {../test_data/list/basic_auth_crack_pin.list} --default-len-min 18\n";
  size_t argc;
  char **argv = arg_vector_from_string(command, &argc);
  Arguments *args = get_arguments(argc, argv, ARGP_NO_EXIT);
  munit_assert_ushort(48, ==, DEFAULT_LEN_MAX);
  munit_assert_ushort(18, ==, DEFAULT_LEN_MIN);
  munit_assert_int('7', ==, DEFAULT_SEPARATOR);
  munit_assert_string_equal(DEFAULT_CHARSET, "koi");
}
int main() {

  test1();
  test2();
  test3();
  test4();
  test_default();

  return 0;
}
