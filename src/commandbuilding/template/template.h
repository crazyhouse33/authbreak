#ifndef GUARDXXX_XXXTEMPLATEH_XXX
#define GUARDXXX_XXXTEMPLATEH_XXX
#include "handler.h"
#include "replace_string.h"
#include <stdbool.h>

typedef struct Template {
	Placeholder* placeholder;
	Handler* handler;
	size_t next_it;//number of iteration (ignore cycle)
} Template;



Template* template_new(Placeholder* placeholder);
/*Create template from placeholder*/

char* template_next(Template* temp);
/*Increment handler and set placeholder to new handler value. Return NULL when handler is done, but automatically reset it (to get cycling behaviour)*/

size_t template_size(Template* temp);
/*Return number of element that template represent*/

void template_reset(Template* temp);
/*Reset handler of template (This have no immediate effect on the string)*/

void template_reset_to(Template* temp, size_t pos);

void template_free(Template* temp);

#endif
