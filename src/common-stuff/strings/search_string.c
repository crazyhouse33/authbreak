#include "search_string.h"
#include <string.h> //strlen
size_t first_diff(char *string1, char *string2, size_t max) {
  for (size_t i = 0; i < max; i++) {
    if (string1[i] != string2[i])
      return i;
  }
  return max;
}

ssize_t get_unique_matching_string(char **list, char *string, size_t until) {
  size_t cpt = 0;
  size_t max_index;
  // The two best matchs
  size_t max1 = 0;
  size_t max2 = 0;
  char *list_string;
  while (list_string = list[cpt++]) {
    size_t compared_len = strlen(list_string);
    if (compared_len < until) // cant match if string is longer
      continue;
    size_t new = first_diff(string, list_string, until);
    if (new == until)            // we have a possible match
      if (compared_len == until) // perfect match
        return cpt - 1;
      else if (new >= max1) {
        max_index = cpt - 1;
        max2 = max1;
        max1 = new;
      }
  }

  if (max1 == 0) // no match
    return SEARCH_ERROR_NO_MATCH;

  if (max1 == max2) // ambiguity
    return SEARCH_ERROR_MATCHS_AMBIGUITY;

  return max_index;
}

bool is_escaped(char *a_char, char escaper) { return (*(a_char - 1) != escaper) || (*(a_char - 2) == escaper); }

char *memchr_not_escaped(char *bloc, char to_found, size_t until, char escaper) {
  // The two first char need special care to not take care of previous memory introducing wierd bugs, we just hardcode it

  if (until <= 0)
    return NULL;
  if (*bloc == to_found)
    return bloc;
  until--;
  if (until <= 0)
    return NULL;
  bloc++;
  if (*(bloc) == to_found && *(bloc - 1) != escaper)
    return bloc;

  /* Dont return escaped character*/
  char *old_found;
  do {
    old_found = bloc;
    bloc = memchr(bloc + 1, to_found, --until);
    until -= bloc - old_found - 1;
  }

  while (bloc != NULL && !is_escaped(bloc, escaper));

  return bloc;
}
