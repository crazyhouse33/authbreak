#include "null_vec.h"
#include "munit.h"

void assert_arg_equal(char **arg1, char **arg2) {
  size_t s1 = get_vector_count((void **)arg1);

  munit_assert_size(s1, ==, get_vector_count((void **)arg2));
  for (size_t i = 0; i < s1; i++) {
    munit_assert_string_equal(arg1[i], arg2[i]);
  }
}

void test_base() {

  char *vec[] = {"authbreak", "--prompt", "18", "curl -f tamere", "--fail", "hey", NULL};
  char **vec1 = (char **)vec;
  size_t size = get_vector_count((void **)vec1);
  munit_assert_size(size, ==, 6);

  char **clone = (char **)dup_vector((void **)vec1);
  assert_arg_equal(clone, vec1);
  munit_assert_ptr(clone, !=, vec1);

  char *exepected[] = {"authbreak", "--prompt", "18", "curl -f tamere", "--fail", "hey", "tamere", "tonpere", NULL};

  char *vec2[] = {"tamere", "tonpere", NULL};
  char **concat = (char **)concatenation_vector((void **)vec1, (void **)vec2);
  assert_arg_equal(exepected, concat);
  munit_assert_ptr(concat, !=, vec1);
  assert_arg_equal(exepected, concat);

  concatenate_vector((void ***)&clone, (void **)vec2);
  assert_arg_equal(clone, exepected);

  put_vector((void ***)&concat, (void *)"tam");

  char *exepected2[] = {"authbreak", "--prompt", "18", "curl -f tamere", "--fail", "hey", "tamere", "tonpere", "tam", NULL};
  assert_arg_equal(exepected2, concat);

  char **vec3 = (char **)create_vector(20);
  for (int i = 0; i < 20; i++) {
    vec3[i] = malloc(sizeof(char) * 20);
  }
  free_vector((void **)vec3);
}

int main() {
  test_base();
  return 0;
}
