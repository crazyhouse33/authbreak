#include "handler.h"
#include "template_parser.h"


void handler_init(Handler* emptypointer, char* template_string, size_t until){
	parse_injection_template(emptypointer, template_string, until);
	handler->buffer=malloc(sizeof(char));
}

char* handler_next(Handler* handler){

}
