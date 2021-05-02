#include "iterator_handler.h"
#include <math.h>
#include "handler.h" //Handler
#include <stdio.h>   //File pointer
#include <stdlib.h>  //malloc
#include <string.h>  //strlen
#include "geometric.h"// geometric_xtoy

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
// way slower(and also I am lazy to implement it). We may change that according to the perf of the tool when ran in parallel (maybe parraleliation will absord every diff allready even for simplest auth process), measure and see
static void construct_next_table(char **pointer_to_table, char *charset, size_t char_num) {
  // take a charset, construct pointer_to_table
  int char_max = get_max(charset, char_num);
  *pointer_to_table = (char *)malloc(sizeof(char) * (char_max + 1));
  size_t i;
  for (i = 0; i < char_num - 1; i++) { // TODO give the furtivity option to randomize the permutation

    (*pointer_to_table)[charset[i]] = charset[i + 1];
  }
  (*pointer_to_table)[charset[i]] = charset[0];
  (*pointer_to_table)[0] = charset[0];//This allow to give us an -1 state for next to end on 0
}

//TODO should just take handler as arg
static void initiate_level(Iterator_needs *it, char *charset) {
	for (int i = 0 ; i < it->len; i++)
		it->current[i] = charset[0]; // TODO Initialize to first char everything for now, give the furtivity option to randomize each level base
	it->current[it->len] = 0;            // adding null char
}

// we pass by args just to avoid useless deferencing for one time func
static char* next_level(Iterator_needs *it, char *charset, size_t len_max) {
	it->len++;
	if (it->len > len_max) { // We need to stop(put it unlikely)
		return NULL;
	}
	initiate_level(it, charset);
	return it->current;
}


//Log n. Not for the faint of the heart
void iterator_handler_reset_to(Handler *handler, size_t pos) {
	Iterator_needs *needs = (Iterator_needs *)handler->special_needs;
	needs->len = handler->options.len_max;
	size_t i=0;
	div_t divresult={0};
	size_t divisor;
	size_t pos_cpy;
	size_t offset;

	// This asume pivot is on the left, and will be broken otherwise
	//skippings the ones to skip, getting real len
		
	while (divresult.quot == 0 && needs->len > handler->options.len_min){
		offset = geometric_xtoy(1, needs->charset_len, handler->options.len_min, needs->len - 1);
		pos_cpy = pos + offset;
		divisor = pow(needs->charset_len, handler->options.len_max - i);
		divresult = div(pos_cpy,divisor);	
		needs->len--;
		i++;
	}
		
	pos -=offset;

	for (i=1; i< needs->len; i++){
		divisor=pow(needs->charset_len, needs->len - i);
		divresult = div(pos,divisor);	
		pos=divresult.rem;
		needs->current[needs->len - i]=handler->options.charset[divresult.quot];
	}

	divresult.rem-=1;
	if (divresult.rem==-1){
		needs->current[0]=0;
	}
	else{
		needs->current[0]=handler->options.charset[divresult.rem];
	}

	needs->current[needs->len] = 0;      
}

// This make the first char of an iterator to be the first one on the next round 
static void it_minus_oneify(Iterator_needs *needs) {
	needs->current[0]=0;
}

void iterator_handler_reset(Handler *handler) {
	Iterator_needs *needs = (Iterator_needs *)handler->special_needs;
	needs->len=handler->options.len_min;
	initiate_level(needs, handler->options.charset);
	it_minus_oneify(needs);
}

size_t iterator_handler_size(Handler* handler){
	Iterator_needs* it= (Iterator_needs*) handler->special_needs;
	return geometric_xtoy(1, it->charset_len, handler->options.len_min, handler->options.len_max);
}

//TODO current could be a shared buffer like for files
void iterator_handler_init_special_needs(Handler *handler) {
	Iterator_needs *needs = malloc(sizeof(Iterator_needs));
	handler->special_needs = needs;
	needs->charset_len = strlen(handler->options.charset);
	needs->current = malloc(sizeof(char) * (1+handler->options.len_max));
	construct_next_table(&needs->charset_next_table, handler->options.charset, needs->charset_len);
	iterator_handler_reset(handler);
}

char *iterator_handler_next(Handler *handler) { // Normal cartesian product

	Iterator_needs *it = (Iterator_needs *)handler->special_needs;
	size_t offset = 0;
	char current_char;
	char last_letter = handler->options.charset[it->charset_len-1];
	do{
		if (offset >=it->len)//level is done
			return next_level(it,handler->options.charset, handler->options.len_max);

		current_char = it->current[offset];
		it->current[offset] = it->charset_next_table[it->current[offset]];
		offset++;
	}
	while ( current_char == last_letter );  

	return it->current;
}

void iterator_handler_free_needs(Handler *handler) {

	Iterator_needs *it = (Iterator_needs *)handler->special_needs;
	free(it->current);
	free(it->charset_next_table);
	free(it);
}
