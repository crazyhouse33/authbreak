#include "handler.h"         //Handler
#include "template_parser.h" //parse_injection_template
#include <stdlib.h>          //malloc

void handler_init(Handler *emptypointer, char *template_string, size_t until, size_t buffer_size) {
  parse_injection_template(emptypointer, template_string, until);
  // TODO no need buffer for the file one (use system buffer and getline)
  emptypointer->buffer = malloc(sizeof(char) * buffer_size);
}

char *handler_next(Handler *handler) { return handler->buffer[handler->pos++]; }

void handler_set(Handler *handler, unsigned long int n) { handler->pos = n; }
