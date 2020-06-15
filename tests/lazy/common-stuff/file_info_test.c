#include "file_info.h"
#include "munit.h"
#include <stdbool.h>
#include <unistd.h>
static void generate_search_executable(char *test_str, char *expected) {
  char *res = search_executable(test_str);
  if (res == NULL)
    munit_assert_ptr(expected, ==, NULL);
  else
    munit_assert_string_equal(expected, res);
}

static void generate_openable(char *test_str, bool expected) {
  bool res = is_openable_file(test_str);
  munit_assert_true(expected == res);
}

static void generate_path_search(char *test_str, char *expected_res) {
  char *res = search_in_path_openable_file(test_str);
  if (res == NULL)
    munit_assert_ptr(expected_res, ==, NULL);
  else
    munit_assert_string_equal(expected_res, res);
}

// TODO do for other platform, better test would also set path to a custom folder that we control
#define EXISTING_FILE_NOT_IN_PATH "/usr/include/stdlib.h"
#define EXISTING_FILE_IN_PATH "ls"
#define EXISTING_FILE_IN_PATH_FULL "/bin/ls"
#define NOT_EXISTING_FILE "/usrarfzsvdvwxv/ixvxwvnxcvcelgude/ssdvtdbool.h"
int main() {

  generate_openable(EXISTING_FILE_IN_PATH, false);
  generate_openable(EXISTING_FILE_NOT_IN_PATH, true);
  generate_openable(NOT_EXISTING_FILE, false);

  generate_path_search(EXISTING_FILE_IN_PATH, EXISTING_FILE_IN_PATH_FULL);
  generate_path_search(NOT_EXISTING_FILE, NULL);
  generate_path_search(EXISTING_FILE_NOT_IN_PATH, NULL);

  generate_search_executable(EXISTING_FILE_IN_PATH, EXISTING_FILE_IN_PATH_FULL);
  generate_search_executable(NOT_EXISTING_FILE, NULL);
  generate_search_executable(EXISTING_FILE_NOT_IN_PATH, EXISTING_FILE_NOT_IN_PATH);

  generate_search_executable("", NULL);

  // test current folder existence(maybe it just depend on path containing .,I am not sure, in that case we should remove thoses tests
  generate_search_executable("file_info_test", "file_info_test");
}
