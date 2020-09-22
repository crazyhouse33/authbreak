#include "concat_string.h"
#include "munit.h"
#include "null_vec.h"
#include "replace_string.h"
#include <stdio.h> //snprintf
#include <string.h>

void strmov_tst() {
  /*overlap*/
  char string[] = "heyhow\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
  strmov(string, string);
  munit_assert_string_equal("heyhow", string);

  strmov(string, string + 3); // src > dst
  munit_assert_string_equal(string, "how");

  strmov(string + 3, string); // dst > src
  munit_assert_string_equal(string, "howhow");

  /*no overlap*/
  char string2[] = "hey\0\0\0\0";
  char string3[] = "how\0\0\0\0";
  strmov(string2 + 3, string3);
  munit_assert_string_equal(string2, "heyhow");
  // testing both directions
  strmov(string3, string2 + 3);
  munit_assert_string_equal(string3, "how");
}

void test_replace(char *new_string) {
  char string[] = "hey, how {you doing}?\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
  char *begin = memchr(string, '{', 2000);
  size_t until = strlen("{you doing}");

  replace_string(begin, until, new_string);
  char *expected = "hey, how ";
  expected = get_concatenation_string(expected, new_string);
  expected = get_concatenation_string(expected, "?");
  munit_assert_string_equal(string, expected);
}

void test_placeholder() {
  // placeholder inlvolve  a lot of tricky stuff, need lot of testing
  char *string_ar = strdup("{}{}tata{}to{}{}");
  char *string = &(string_ar[0]);
  char *s1 = memchr(string, '{', 20);
  char *s2 = memchr(s1 + 1, '{', 20);
  char *s3 = memchr(s2 + 1, '{', 20);
  char *s4 = memchr(s3 + 1, '{', 20);
  char *s5 = memchr(s4 + 1, '{', 20);
  char *e1 = memchr(string, '}', 20);
  char *e2 = memchr(e1 + 1, '}', 20);
  char *e3 = memchr(e2 + 1, '}', 20);
  char *e4 = memchr(e3 + 1, '}', 20);
  char *e5 = memchr(e4 + 1, '}', 20);

  Placeholder *p1 = placeholder_new(&string, s1, e1);
  Placeholder *p2 = placeholder_new_depend(p1, s2, e2);
  Placeholder *p3 = placeholder_new_depend(p2, s3, e3);
  Placeholder *p4 = placeholder_new_depend(p3, s4, e4);
  Placeholder *p5 = placeholder_new_depend(p4, s5, e5);

  munit_assert_size(p1->begin, ==, s1 - string);
  munit_assert_size(p2->begin, ==, s2 - string);
  munit_assert_size(p3->begin, ==, s3 - string);
  munit_assert_size(p5->begin, ==, s5 - string);

  munit_assert_size(p1->size_place, ==, 2);
  munit_assert_size(p2->size_place, ==, 2);
  munit_assert_size(p3->size_place, ==, 2);

  munit_assert_size(*(p1->size_of_string), ==, strlen(string));
  munit_assert_size(*(p1->max_size), ==, strlen(string));
  size_t oldmax = *(p1->max_size);
  placeholder_switch(p3, "tata");
  munit_assert_size(*(p1->max_size), >, oldmax); // got affected by p3 switch
  char *expect = "{}{}tatatatato{}{}";
  munit_assert_string_equal(expect, string);
  munit_assert_size(*(p1->size_of_string), ==, strlen(expect));
  placeholder_switch(p1, "nono");

  char *expect2 = "nono{}tatatatato{}{}";

  munit_assert_size(p3->begin, ==, 10); // got affected by p3 switch

  munit_assert_string_equal(expect2, string);

  placeholder_switch(p1, "no");

  munit_assert_string_equal("no{}tatatatato{}{}", string);
  munit_assert_size(*(p2->size_of_string), ==, strlen("no{}tatatatato{}{}"));
  placeholder_switch(p1, "");

  munit_assert_string_equal("{}tatatatato{}{}", string);
  munit_assert_size(0, ==, p2->begin);
  munit_assert_size(0, ==, p1->begin);

  // ensuring no weird bug cause of end
  placeholder_switch(p5, "h");

  munit_assert_string_equal("{}tatatatato{}h", string);

  placeholder_switch(p4, "hey");

  munit_assert_string_equal("{}tatatatatoheyh", string);

  placeholder_switch(p5, "NONO");

  munit_assert_string_equal("{}tatatatatoheyNONO", string);
  placeholder_switch(p4, "");

  munit_assert_string_equal("{}tatatatatoNONO", string);
}

void test_placeholder_long() {//May trigger memory problemes
  char *string_ar = strdup("{}{aa}");
  char *string = &(string_ar[0]);
  char *s1 = memchr(string, '{', 20);
  char *s2 = memchr(s1 + 1, '{', 20);
  char *e1 = memchr(string, '}', 20);
  char *e2 = memchr(e1 + 1, '}', 20);

  char to_concat[1000];
  char expected[2000];
  to_concat[0]=0;

  Placeholder *p1 = placeholder_new(&string, s1, e1);
  Placeholder *p2 = placeholder_new_depend(p1, s2, e2);
  for (int i=0;i<1000;i++){
	to_concat[i+1]=0;
	to_concat[i]='a';
  	placeholder_switch(p1, to_concat);
  	placeholder_switch(p2, to_concat);
	int size= i+1;
	memcpy(expected, to_concat, size);
	memcpy(expected+size, to_concat, size+1);
        munit_assert_string_equal(expected, string);
  }

}

void test_parser() {
  char *test_str7 = "tototata";
  Placeholder **placeholders7 = placeholder_parse_string(&test_str7, '{', '}', '\\');
  size_t size7 = get_vector_count((void **)placeholders7);
  munit_assert_size(size7, ==, 0);

  char *test_str4 = "{}";
  Placeholder **placeholders4 = placeholder_parse_string(&test_str4, '{', '}', '\\');
  size_t size4 = get_vector_count((void **)placeholders4);
  munit_assert_size(size4, ==, 1);

  char *test_str3 = "{}ro{}";
  Placeholder **placeholders3 = placeholder_parse_string(&test_str3, '{', '}', '\\');
  size_t size3 = get_vector_count((void **)placeholders3);
  munit_assert_size(size3, ==, 2);

  char *test_str6 = "{}{}";
  Placeholder **placeholders6 = placeholder_parse_string(&test_str6, '{', '}', '\\');
  size_t size6 = get_vector_count((void **)placeholders6);
  munit_assert_size(size6, ==, 2);

  char *test_str = "{}hey{}{\\{}\\}";
  Placeholder **placeholders = placeholder_parse_string(&test_str, '{', '}', '\\');
  size_t size = get_vector_count((void **)placeholders);
  munit_assert_size(size, ==, 3);
  char *test_str2 = "**hey***\\**\\*";
  Placeholder **placeholders2 = placeholder_parse_string(&test_str2, '*', '*', '\\');
  size_t size2 = get_vector_count((void **)placeholders2);
  munit_assert_size(size2, ==, 3);

  char *test_str5 = "";
  Placeholder **placeholders5 = placeholder_parse_string(&test_str5, '{', '}', '\\');
  size_t size5 = get_vector_count((void **)placeholders5);
  munit_assert_size(size5, ==, 0);
}

int main() {

  strmov_tst();

  char *replace_bigger = "are youu doiiiinggggg";
  char *replace_shorter = "you do";
  char *replace_same = "you doooo";
  char *replace_empty = "";
  test_replace(replace_bigger);
  test_replace(replace_shorter);
  test_replace(replace_same);
  test_replace(replace_empty);


  test_placeholder_long();//Dont forget to put it after the normal one
  test_placeholder();
  test_parser();
  return 0;
}
