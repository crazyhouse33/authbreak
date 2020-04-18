#include "concat_string.h"
#include <stdlib.h> //malloc
#include <string.h> //memcopy
char *sstrcat(char *string1, char *string2) {
  size_t s1 = strlen(string1);
  size_t s2 = strlen(string2);
  char *res = realloc(string1, sizeof(char) * (s1 + s2));
  memcpy(res + s1, string2, s2);
  return res;
}

char *sstrcat_copy(char *string1, char *string2) {
  size_t s1 = strlen(string1);
  size_t s2 = strlen(string2);
  char *res = malloc(sizeof(char) * (s1 + s2));
  memcpy(res, string1, s1);
  memcpy(res + s1, string2, s2);
  return res;
}
