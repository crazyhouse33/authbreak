#include "template.h"

Template* template_new(Placeholder* placeholder){
	Template* ret = malloc(sizeof(Template));
	ret->placeholder = placeholder;
	ret->handler=handler_new(*placeholder->base_string + placeholder->begin + 1, placeholder->size_place - 2);
	return ret;
}

bool template_next(Template* temp){
	char* next_str = handler_next(temp->handler);
	if (next_str == NULL){
		handler_reset(temp->handler);
		placeholder_switch(temp->placeholder, handler_next(temp->handler));
		return true;
	}
	placeholder_switch(temp->placeholder, next_str);
	return false;
}

/*Return number of element that template represent*/
size_t template_size(Template* temp){
	return handler_size(temp->handler);
}

void template_free(Template* temp){
	handler_free(temp->handler);
	//TODO implement placeholderfree
}

void template_reset(Template* temp){
	handler_reset(temp->handler);
}
