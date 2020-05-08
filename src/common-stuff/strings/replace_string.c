#include "replace_string.h"
#include "concat_string.h"
#include "error.h"
#include "max.h"
#include "null_vec.h" //vector of placeholder
#include <stdbool.h>
#include <stdlib.h> //malloc
#include <string.h> //memmov

void *strmov(char *dst, char *src)
/*strmov for strings, we cannot use memcpy or stcpy because the pointer assume to overlap  */
{
  // copy until we copy a null

  if (dst < src) // if dst > src we can copy until
    do
      *(dst++) = *(src++);
    while (*(src - 1));
  else                                  // it may or not be more efficient to copy from right to left
    memmove(dst, src, strlen(src) + 1); //+1 for the null
}

void same_size_replace_fast(char *begin, char *replacement, size_t replacement_size) { memcpy(begin, replacement, replacement_size); }

void replace_string_fast(char *begin, size_t how_many_chars, char *replacement, size_t replacement_size) {

  strmov(begin + replacement_size, begin + how_many_chars);
  same_size_replace_fast(begin, replacement, replacement_size);
}

Placeholder *placeholder_new(char **base_string, char *begin, char *end) {

  Placeholder *placeholder = malloc(sizeof(Placeholder));
  placeholder->base_string = base_string;
  placeholder->begin = begin - *base_string;
  placeholder->size_place = end - begin + 1;
  size_t initial_size = strlen(*base_string);
  placeholder->size_of_string = malloc(sizeof(size_t));
  placeholder->max_size = malloc(sizeof(size_t));
  *(placeholder->size_of_string) = initial_size;
  *(placeholder->max_size) = initial_size;
  // TODO evergrowing pointer
  placeholder->dependant_placeholders = malloc(sizeof(Placeholder **));
  *placeholder->dependant_placeholders = (Placeholder **)create_vector(0);
  placeholder->level = 0; // so level point directely where to aime in dependance
  return placeholder;
}

Placeholder *placeholder_new_depend(Placeholder *base_placeholder, char *begin, char *end) {

  Placeholder *placeholder = malloc(sizeof(Placeholder));
  placeholder->base_string = base_placeholder->base_string;
  placeholder->begin = begin - *placeholder->base_string;
  placeholder->size_place = end - begin + 1;
  placeholder->size_of_string = base_placeholder->size_of_string;
  placeholder->max_size = base_placeholder->max_size;
  placeholder->dependant_placeholders = base_placeholder->dependant_placeholders;
  put_vector((void ***)base_placeholder->dependant_placeholders, (void *)placeholder);
  placeholder->level = base_placeholder->level + 1;
  return placeholder;
}

void replace_string(char *begin, size_t until, char *replacement) {
  size_t replacement_size = strlen(replacement);
  replace_string_fast(begin, until, replacement, replacement_size);
}

static void _placeholder_fix_memory(Placeholder *placeholder) {

  if (*(placeholder->size_of_string) > *(placeholder->max_size)) {                   // too big
    *(placeholder->max_size) = (PLACEHOLDERMARGIN + *(placeholder->size_of_string)); // all the dependant placeholders are actualized at once
    *(placeholder->base_string) = realloc(*(placeholder->base_string), sizeof(char) * *(placeholder->max_size));
  }
}

void placeholder_switch(Placeholder *placeholder, char *string) {
  size_t new_subpart_len = strlen(string);
  int diff = new_subpart_len - placeholder->size_place;
  if (diff == 0) // Same size, just write in place
    same_size_replace_fast(placeholder->begin + *(placeholder->base_string), string, placeholder->size_place);
  else { // Not the same size
    *(placeholder->size_of_string) += diff;
    if (diff > 0)                           // If bigger may have memory overflow
      _placeholder_fix_memory(placeholder); // size problem and memory management of structure is resolved

    replace_string_fast(placeholder->begin + *(placeholder->base_string), placeholder->size_place, string, new_subpart_len);
    // actualizing new place adjustment
    placeholder->size_place += diff;
    Placeholder **son = *placeholder->dependant_placeholders + placeholder->level;
    while (*son != NULL) {
      (*son)->begin += diff;
      son++;
    }
  }
}

static bool is_escaped(char *a_char, char escaper) { return (*(a_char - 1) != escaper) || (*(a_char - 2) == escaper); }
static char *memchr_not_escaped(char *bloc, char to_found, size_t until, char escaper) {
  // The two first char need special attention to not take care of previous memory introducing wierd bugs

  if (*bloc == to_found)
    return bloc;
  if (*(++bloc) == to_found && *(bloc - 1) != escaper)
    return bloc;
  until -= 2;
  bloc--;
  /* Dont return escaped character*/
  char *old_found;
  do {
    old_found = bloc;
    bloc = memchr(bloc + 1, to_found, until);
    until -= bloc - old_found;
  }

  while (bloc != NULL && !is_escaped(bloc, escaper));

  return bloc;
}

Placeholder **placeholder_parse_string(char *string, char opener, char closer, char escaper) {
  size_t to_parse = strlen(string) + 1; //+1 cause end=string-1 trick
  char *begin;
  Placeholder **res_vector = (Placeholder **)create_vector(0);
  ;
  size_t res_size = 0;
  char *end = string - 1;
  while (begin = memchr_not_escaped(end + 1, opener, to_parse, escaper)) { // there is a begin

    to_parse -= begin - end;
    end = memchr_not_escaped(begin + 1, closer, --to_parse, escaper);
    if (end == NULL)
      critical_error_msg(1, "Opened template not closed:\n%s", begin);

    // valid template, between begin and end
    Placeholder *new_placeholder;
    if (res_size == 0)
      new_placeholder = placeholder_new(&string, begin, end);
    else
      new_placeholder = placeholder_new_depend(res_vector[res_size - 1], begin, end);

    put_vector((void ***)&res_vector, (void *)new_placeholder);
    res_size++;
  }
  return res_vector;
}

/*TODO This is still improvable a bit cause we can still define a function to replace a placeholder** to group of lacholders, and do everything at the same time(computing every diff first, make the
 * string bigger accordingly and add cumulative diff to begin of every dependance*/
