#include "handler.h"
#include "replace_string.h"
#include <stdbool.h>

typedef struct Template {
	Placeholder* placeholder;
	Handler* handler;
} Template;



Template* template_new(Placeholder* placeholder);
/*Create template from placeholder*/

bool template_next(Template* temp);
/*Increment handler and set placeholder to new handler value. Return true if handler is done*/



