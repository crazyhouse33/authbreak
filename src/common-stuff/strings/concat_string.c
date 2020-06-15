#include "concat_string.h"
#include <stdlib.h> //malloc
#include <string.h> //memcopy

size_t concat_string_fast(char **string1, char *string2, size_t s1, size_t s2) {
  size_t new_size = s1 + s2;
  *string1 = realloc(*string1, sizeof(char) * (new_size + 1));
  memcpy(*string1 + s1, string2, s2 + 1);
  return new_size;
}

size_t concat_string_fast_left(char **string1, char *string2, size_t s1) {
  size_t s2 = strlen(string2);
  return concat_string_fast(string1, string2, s1, s2);
}

size_t concat_string(char **string1, char *string2) {
  size_t s1 = strlen(*string1);
  size_t s2 = strlen(string2);
  return concat_string_fast(string1, string2, s1, s2);
}

char *get_concatenation_string(char *string1, char *string2) {
  char *clone = strdup(string1);
  concat_string(&clone, string2);
  return clone;
}

char *get_concatenation_string_fast(char *string1, char *string2, size_t s1, size_t s2) {
  char *clone = strdup(string1);
  concat_string_fast(&clone, string2, s1, s2);
  return clone;
}

size_t concat_string_cut(char **string1, char *string2, size_t s2_len) {
  size_t s1 = strlen(*string1);
  size_t size = concat_string_fast(string1, string2, s1, s2_len); // this contain a read overflow of 1 bit
  (*string1)[size] = 0;
  return size;
}

size_t concat_char(char **string, char c) { return concat_string_cut(string, &c, 1); }
