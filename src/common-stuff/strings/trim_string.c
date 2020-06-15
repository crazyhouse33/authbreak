#include "trim_string.h"
#include <ctype.h>  //isspace
#include <stdlib.h> //malloc
#include <string.h> //strcopy and stuff

size_t consec_not_white_number(char *str) {
  size_t res = 0;
  while (*(str + res) && !isspace(*((str + res))))
    res++;
  return res;
}

void left_trim_in_place(char **string) {
  /*Make given pointer point on the first non white character*/
  while (**string && isspace(**string)) {
    (*string)++;
  }
  // now string point on non empty char
}

void point_to_last_white(char *begin, char **string_end) {

  /*Make string_end point to the last white on the end of the string  */
  while (*string_end - 1 > begin && isspace(*(*string_end - 1))) {
    (*string_end)--;
  }
}

char *get_pointer_to_last_white(char *begin, char *string_end) {
  /*Get pointer to the last white on the end of the string  */
  char *new_pointer = string_end;
  point_to_last_white(begin, &new_pointer);
  return new_pointer;
}

void right_trim_in_place(char *begin, char **string_end) {
  /*Add a null char just after first non white character on the left of the pointer*/
  point_to_last_white(begin, string_end);
  **string_end = 0;
}

char *right_trim(char *begin, char *string_end) {
  char *new_pointer = string_end;
  right_trim_in_place(begin, &new_pointer);
  return new_pointer;
}

void trim_in_place(char **string, char **string_end) {
  /*Make string point on first non white character and null character after first non white character on the left, and make string end point to the new end of the string*/
  left_trim_in_place(string);
  right_trim_in_place(*string, string_end);
}

char *trim_in_place_preserve_left(char *string, char **string_end) {
  char *new_string = left_trim(string);
  right_trim_in_place(string, string_end);
  return new_string;
}
void trim_in_place_preserve_right(char **string, char *string_end) {
  left_trim_in_place(string);
  right_trim(*string, string_end);
}

char *get_after_sep_part(char *string, char sep, size_t until) {
  /*Return a pointer pointing to the first character after the specified separator or return the begining of string if no separator found*/
  char *sep_pointer = memchr(string, sep, until);
  if (sep_pointer == NULL)
    return string;
  return sep_pointer + 1;
}

char *left_trim(char *string) {
  char *new_pointer = string;
  /*Make given pointer point on the first non white character*/
  left_trim_in_place(&new_pointer);

  return new_pointer;
}

char *trim_change_end(char *string_begin, char *string_end) {
  char *new_begin = left_trim(string_begin);
  point_to_last_white(string_begin, &string_end);
  unsigned offset = string_end - new_begin;
  char *copy = malloc(offset * sizeof(char));
  strncpy(copy, new_begin, offset);
  return copy;
}

char *trim(char *string_begin, char *string_end) {
  char *new_begin = left_trim(string_begin);
  char *new_end = get_pointer_to_last_white(string_begin, string_end);
  unsigned offset = new_end - new_begin;
  char *copy = malloc(offset * sizeof(char));
  strncpy(copy, new_begin, offset);
  return copy;
}

void trim_point(char **begin, char **end) {
  left_trim_in_place(begin);
  point_to_last_white(*begin, end);
}
