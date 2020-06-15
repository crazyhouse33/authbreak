#include "handler.h"
#include "munit.h"
#include "test_unicity.h"

Handler *handler;
Handler *fake_handler;

char *generate_once(int first_iter) {
  char *trash;
  if (first_iter) {
    trash = handler_get_current(fake_handler);
    return handler_get_current(handler);
  }

  trash = handler_next(fake_handler);
  return handler_next(handler);
}

void assert_handler_generic_iteration_test(Handler *the_handler, Handler *the_fake_handler,
                                           size_t expected_cycle_size) { // fake handler is a same type handler to trap board effect bugs inside handler classes
  handler = the_handler;
  fake_handler = the_fake_handler;

  assert_iteration_test(generate_once, expected_cycle_size);

  handler_free(handler);
  handler_free(fake_handler);
}
