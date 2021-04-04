#include "replace_string.h"
#include "concat_string.h"
#include "error.h"
#include "max.h"
#include "null_vec.h"      //vector of placeholder
#include "search_string.h" //escape memchr
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
	  size_t new_max=PLACEHOLDERMARGIN + *(placeholder->size_of_string);
    *(placeholder->max_size) = new_max; // all the dependant placeholders are actualized at once
    *(placeholder->base_string) = realloc(*(placeholder->base_string), sizeof(char) * (new_max+1));//+1 cause null char is no accounted
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
    placeholder->size_place = new_subpart_len;
    Placeholder **son = *placeholder->dependant_placeholders + placeholder->level;
    while (*son != NULL) {
      (*son)->begin += diff;
      son++;
    }
  }
}

// We could iterate with 2 less variable( current and final)
Placeholder **placeholder_parse_string(char **string, char opener, char closer, char escaper, size_t* size) {
  size_t to_parse = strlen(*string); // we dont include \0 in the search
  char *final_end = *string + to_parse;
  char *begin;
  Placeholder **res_vector = (Placeholder **)create_vector(0);
  ;
  *size = 0;
  char *end;
  char *current = *string;
  while (begin = memchr_not_escaped(current, opener, to_parse, escaper)) { // there is a begin

    current = begin + 1;
    to_parse = final_end - current;
    end = memchr_not_escaped(current, closer, to_parse, escaper);
    if (end == NULL)
      controlled_error_msg(2, "Opened template not closed:\n%s", begin);

    current = end + 1;
    to_parse = final_end - current;

    // valid template, between begin and end
    Placeholder *new_placeholder;
    if (*size == 0)
      new_placeholder = placeholder_new(string, begin, end);
    else
      new_placeholder = placeholder_new_depend(res_vector[*size - 1], begin, end);

    put_vector((void ***)&res_vector, (void *)new_placeholder);
    (*size)++;
  }
  return res_vector;
}

/*TODO This is still optimizable cause we can still define a function to replace a placeholder** to group of lacholders, and do everything at the same time(computing every diff first, make the
 * string bigger accordingly and add cumulative diff to begin of every dependance*/
