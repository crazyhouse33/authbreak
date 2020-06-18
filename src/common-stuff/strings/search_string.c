#include "search_string.h"
#include "max.h"
#include "error.h"
#include <string.h> //strlen
#include <stdlib.h> //strtol
size_t common_substring_size(char *string1, char *string2, size_t max) {
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

    compared_len = MIN(compared_len, until);
    size_t common_part = common_substring_size(list_string, string, compared_len + 1); // counting \0

    if (common_part < until) // cannot match if bigger
      continue;

    if (common_part >= max1) {
      max_index = cpt - 1;
      max2 = max1;
      max1 = common_part;
    }
  }

  if (max1 == 0) // no match
    return SEARCH_ERROR_NO_MATCH;

  if (max1 == max2) // ambiguity
    return SEARCH_ERROR_MATCHS_AMBIGUITY;

  return max_index;
}

// I passed A LOT OF TIME trying to merge the following functions because I had the impression it could be done cleanely but it was just getting into quoting hell, so I will just copy past and fuck it
ssize_t get_unique_matching_string_tolerant(char **list, char *string, size_t until, char **end_valid) {
  size_t cpt = 0;
  size_t max_index;
  // The two best matchs
  size_t max1 = 0;
  size_t max2 = 0;
  char *list_string;
  while (list_string = list[cpt++]) {
    size_t compared_len = strlen(list_string);
    compared_len = MIN(compared_len, until);
    size_t common_part = common_substring_size(list_string, string, compared_len); // counting \0

    if (common_part >= max1) {
      *end_valid = string + common_part - 1;
      max_index = cpt - 1;
      max2 = max1;
      max1 = common_part + (common_part == compared_len);
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

unsigned long int parse_positive_int_intolerant(char *int_str, int error_status,char* error_format) {
char* valid_end;
long int target = strtol(int_str, &valid_end, 0);

  if (target < 0 && *valid_end)
    controlled_error_msg(error_status, error_format, int_str);

  return (unsigned long int) target;
}


long int parse_int_intolerant(char *int_str, int error_status,char* error_format) {
char* valid_end;
long int target = strtol(int_str, &valid_end, 0);

  if (*valid_end)
    controlled_error_msg(error_status, error_format, int_str);

  return target;
}

