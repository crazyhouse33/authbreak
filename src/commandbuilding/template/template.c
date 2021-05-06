#include "template.h"

Template* template_new(Placeholder* placeholder){
	Template* ret = malloc(sizeof(Template));
	ret->placeholder = placeholder;
	ret->handler=handler_new(*placeholder->base_string + placeholder->begin + 1, placeholder->size_place - 2);
	ret->next_it=0;
	template_next(ret); //Setting placeholder to firs value
	return ret;
}

char* template_next(Template* temp){
	char* next_str = handler_next(temp->handler);
	if (next_str == NULL){
		template_reset(temp);
		return NULL;
	}
	temp->next_it++;
	placeholder_switch(temp->placeholder, next_str);
	return next_str;
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
	temp->next_it=0;
}

void template_reset_to(Template* temp, size_t pos){
	//necessarry for 0 to work
	if (pos==0)
		template_reset(temp);
	while (temp->next_it != pos)
		template_next(temp);
}


