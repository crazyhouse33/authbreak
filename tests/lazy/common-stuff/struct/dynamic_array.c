#include "dynamic_array.h"
#include "munit.h"

void test_alloc() {

  Dynamic_Array *toto1 = new_dynamic_array(0);
  munit_assert_size(toto1->size, ==, 1);

  Dynamic_Array *toto2 = new_dynamic_array(2);
  munit_assert_size(toto2->size, ==, 4);

  Dynamic_Array *toto3 = new_dynamic_array(43);
  munit_assert_size(toto3->size, ==, 64);

  Dynamic_Array *toto4 = new_dynamic_array(3);
  munit_assert_size(toto4->size, ==, 4);
}

void test_it() {
  int intar[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int size_int = sizeof(intar) / sizeof(int);

  char *stringar[] = {"str1", "str2", "str3", "str4", "str5", "str6", "str7", "str8", "str9", "str10"};
  int size_str = sizeof(stringar) / sizeof(char *);

  Dynamic_Array *strda = new_dynamic_array(0);
  Dynamic_Array *intda = new_dynamic_array(0);

  for (int i = 0; i < size_int; i++) {
    int *point = &intar[i];
    dynamic_array_put(intda, (void *)point, i);
  }

  for (int i = 0; i < size_str; i++) {
    dynamic_array_put(strda, (void *)stringar[i], i);
  }

  for (int i = 0; i < size_int; i++) {
    int the_int = *(int *)intda->array[i];

    munit_assert_int(intar[i], ==, the_int);
  }

  for (int i = 0; i < size_str; i++) {

    munit_assert_string_equal(stringar[i], strda->array[i]);
  }

  dynamic_array_put(strda, (void *)"I am far", 15000);
}

int main() {
  test_alloc();
  test_it();

  return 0;
}
