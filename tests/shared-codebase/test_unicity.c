#include "test_unicity.h"
#include "dynamic_array.h"
#include "munit.h"
#include <string.h> // strdup
static size_t count(char *string, char **res, ssize_t size_res) {
  size_t cpt = 0;
  for (ssize_t i = 0; i < size_res; i++)
    if (!strcmp(string, res[i]))
      cpt++;
  return cpt;
}

void assert_not_present(char *string, char **result, size_t size_res) { munit_assert_size(count(string, result, size_res), >=, 1); }

void assert_present(char *string, char **result, size_t size_res) { munit_assert_size(count(string, result, size_res), <=, 0); }

void assert_is_permutation(char **res1, char **res2, size_t size1, size_t size2) {
  munit_assert_size(size1, ==, size2);
  for (int i = 0; i < size1; i++) {
    munit_assert_size(count(res1[i], res1, size1), ==, count(res1[i], res2, size2));
  }
}

void assert_all_unique(char **res, size_t size) {
  for (int i = size - 1; i >= 0; i--) {
    munit_assert_size(count(res[i], res, i - 1), ==, 0);
  }
}

int first_iter = 1;
char **generate_iteration_history(size_t *s, char *generate(int)) {

  // TODO use ever growing pointer

  Dynamic_Array *res = new_dynamic_array(256);

  char *it;
  size_t cpt = 0;
  while (it = generate(first_iter)) {
    first_iter = 0;
    dynamic_array_put(res, strdup(it), cpt++);
  }
  *s = cpt;
  return (char **)res->array;
}

void assert_iteration_test(char *generate(int), size_t expected_cycle_size) { // We test than iteration is permutation/uniq/ciclique

  size_t size1;
  size_t size2;
  first_iter = 1;
  char **history = generate_iteration_history(&size1, generate);
  first_iter = 1;
  char **history2 = generate_iteration_history(&size2, generate);
  munit_assert_size(size1, ==, expected_cycle_size);

  assert_all_unique(history, size1);
  assert_is_permutation(history, history2, size1, size2);
  return history;
}
