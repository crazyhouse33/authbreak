#include "handler.h" //Handler
#include "file_handler.h"
#include "iterator_handler.h"
#include "template_parser.h" //parse_injection_template
#include <stdlib.h>          //malloc

// To realize polymorphism, we use a big switch rather than function pointer for performance reason, unintuitively. (The switch way allow compiler to optimize way more than a function pointer. The
// pointer way does not allow the compiler to inline, to pass arg in register...).

DEFINE_ENUM(Handler_type, "\"%s\" is not a valid template type, chose amongs this options: \n%s\n", "\"%s\" is ambigious as template type, choose among: \n%s\n", HANDLER_TYPE);

//TODO this should take main_template and options as arguments, not a string
Handler *handler_new(char *template_string, size_t until) {
  Handler *res = malloc(sizeof(Handler));
  handler_init(res, template_string, until);
  return res;
}

void handler_init(Handler *emptypointer, char *template_string, size_t until) {
  parse_injection_template(emptypointer, template_string, until); // get type and affect options
  switch (emptypointer->type) {
  case file:
    file_handler_init_special_needs(emptypointer);
    break;

  case iterator:
    iterator_handler_init_special_needs(emptypointer);
    break;
  }
}

/*TODO For better performance with the switch prediction, order the placeholders by type of handler in the iteration*/
char *handler_next(Handler *handler) {
  switch (handler->type) {
  case file:
    return file_handler_next(handler);
    break;

  case iterator:
    return iterator_handler_next(handler);
    break;
  }
}

char *handler_get_current(Handler *handler) {
  switch (handler->type) {
  case file:
    return file_handler_get_current(handler);
    break;

  case iterator:

    return iterator_handler_get_current(handler);

    break;
  }
}

void handler_free(Handler *handler) {
  switch (handler->type) {
  case file:
    file_handler_free_needs(handler);
    break;

  case iterator:

    iterator_handler_free_needs(handler);
    break;
  }
  free(handler->main_component);
  free(handler);
}


size_t handler_size(Handler *handler) {
switch (handler->type) {
  case file:
    return file_handler_size(handler);
    break;

  case iterator:

    return iterator_handler_size(handler);
    break;
  }
}
Handler *get_dummy_handler() { return handler_new("0:0, type=iterator", 18); }
