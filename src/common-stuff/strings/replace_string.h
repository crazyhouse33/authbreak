#include <stddef.h>//size_t
#ifndef PLACEHOLDERMARGIN
#define PLACEHOLDERMARGIN 100
#endif


typedef struct Placeholder Placeholder;
struct Placeholder {
	
	  char** base_string; //one level of indirection cause need to be reallocable:w
	  size_t begin;// cant be a pointer to char since base_string is reallocable
	  size_t size_place;
	  
	  //Dependence gestionning
	  Placeholder*** dependant_placeholders;//Any modification switch on a dependance_hierarchy trigger update for following placeholder in the hierarchy
	  size_t level;//level in the hierarchy

	
	  //memory management
	  // This pointers are shared between all dependances in order that very change to the memory pointed is propragated without mor work
	  size_t* size_of_string;//We realloc by big chunk, when the size of string is to be bigger than max size
	  size_t* max_size;



};

void *strmov(char *dst, char *src);
/*memmov for str */

void same_size_replace_fast(char* begin, char* replacement, size_t replacement_size);
/*Write replacement at begin*/


//TODO could be usefull to return new size of basestring, not for my usage tho
void replace_string_fast(char* position, size_t howmanychar ,char* replacement, size_t len_of_replacement);
/*Function to replace subpart of strings. The  howmany char including the begin one is replaced by string. Does not check memory problems. if howmanychar== len_of_replacement you should use same_size_replace_fast instead */

void replace_string(char* position, size_t until ,char* replacement);
/*Same as upper one but compute len himself*/

Placeholder* placeholder_new(char** base_string, char* begin, char* end);
/*Constructor for a root level placeholder*/

Placeholder *placeholder_new_depend(Placeholder *base_placeholder, char *begin, char *end);
/*Link a placeholder to an exesting one*/

void placeholder_switch(Placeholder* placeholder, char* string);
/*Switch the portion delimited byt the placeholder with a string, actualize the size to keep track of the place, actualize the positions of the dependent placeholders*/

Placeholder** placeholder_parse_string(char** string, char opener, char closer, char escaper);
/*Same but also check escaping with the escaper of your choice*/


