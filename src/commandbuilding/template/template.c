#include "template.h"

Template* template_new(Placeholder* placeholder){
	Template* ret = malloc(sizeof(Template));
	ret->placeholder = placeholder;
	ret->handler=handler_new(*placeholder->base_string + placeholder->begin + 1, placeholder->size_place - 2);
	placeholder_switch(placeholder, handler_get_current(ret->handler));
	return ret;
}

bool template_next(Template* temp){
	char* next_str = handler_next(temp->handler);
	if (next_str == NULL){
		placeholder_switch(temp->placeholder, handler_get_current(temp->handler));
		return true;
	}
	placeholder_switch(temp->placeholder, next_str);
	return false;
}


