#include "iterator_handler.h"
#include "handler.h" //Handler
#include <stdio.h>   //File pointer
#include <stdlib.h>  //malloc
#include <string.h>  //strlen

#define INITIAL_ITERATOR_LEVEL_LIMIT 32
#define ITERATOR_LEVEL_LIMIT_UPDATE 32

int get_max(char *charset, size_t size) {
  int max = -1;
  for (int i = 0; i < size; i++)
    if (charset[i] > max)
      max = charset[i];
  return max;
}

// TODO Done once, it's a permutation lut for the next character according to charset, notice how we loose a lot of memory if we use utf-8, this is a trade of speed/space because dictionnary access is
// way slower. We may change that according to the perf of the tool when ran in parallel (maybe parraleliation will absord every diff allready even for simplest auth process), measure and see
static void construct_next_table(char **pointer_to_table, char *charset) {
  // take a charset, construct pointer_to_table
  size_t char_num = strlen(charset);
  int char_max = get_max(charset, char_num);
  *pointer_to_table = (char *)malloc(sizeof(char) * char_max);
  size_t i;
  for (i = 0; i < char_num - 1; i++) { // TODO give the furtivity option to randomize the permutation

    (*pointer_to_table)[charset[i]] = charset[i + 1];
  }
  (*pointer_to_table)[charset[i]] = charset[0];
}

static void initiate_level(Iterator_needs *it, char *charset) {
  // We test string of size old +1

  if (it->len > it->real_size) { // mananaging memory problemœ
    size_t new_size = it->len + ITERATOR_LEVEL_LIMIT_UPDATE;
    it->current = realloc(it->current, new_size * sizeof(char));
    it->real_size = new_size;
  }
  size_t i;
  for (i = 0; i < it->len; i++)
    it->current[i] = charset[0]; // TODO Initialize to first char everything for now, give the furtivity option to randomize each level base
  it->current[i] = 0;            // adding null char
}

static void next_level(Iterator_needs *it, char *charset) {
  it->len++;
  initiate_level(it, charset);
}

static void iterator_handler_reset(Handler *handler) {
  Iterator_needs *needs = (Iterator_needs *)handler->special_needs;
  needs->len = handler->options.len_min;
  if (needs->len > 0) // if different from 0 we setup properly
    initiate_level(needs, handler->options.charset);
  else
    needs->current[0] = 0; // if 0 first guess must be null char, we let iteration call next_level naturally
}

void iterator_handler_init_special_needs(Handler *handler) {
  Iterator_needs *needs = malloc(sizeof(Iterator_needs));
  handler->special_needs = needs;
  needs->real_size = INITIAL_ITERATOR_LEVEL_LIMIT;
  needs->current = malloc(sizeof(char) * INITIAL_ITERATOR_LEVEL_LIMIT);
  construct_next_table(&needs->charset_next_table, handler->options.charset);
  iterator_handler_reset(handler);
}

char *iterator_handler_next(Handler *handler) { // Normal cartesian product

  Iterator_needs *it = (Iterator_needs *)handler->special_needs;
  ssize_t offset = -1;
  char *current_char; // we start on the first letter
  do {
    if (++offset >= it->len) {                   // the level is done
      if (it->len >= handler->options.len_max) { // We need to stop(put it unlikely)
        iterator_handler_reset(handler);
        return NULL;
      }
      next_level(it, handler->options.charset); // passing to next level
      return it->current;
    }
    it->current[offset] = it->charset_next_table[it->current[offset]];
  } while (it->current[offset] == handler->options.charset[0]);

  return it->current;
}

char *iterator_handler_get_current(Handler *handler) {
  Iterator_needs *it = (Iterator_needs *)handler->special_needs;
  return it->current;
}

void iterator_handler_free_needs(Handler *handler) {

  Iterator_needs *it = (Iterator_needs *)handler->special_needs;
  free(it->current);
  free(it->charset_next_table);
  free(it);
}
