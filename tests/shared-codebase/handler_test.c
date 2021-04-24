#include "handler.h"
#include "munit.h"
#include "test_unicity.h"

Handler *handler;
Handler *fake_handler;

char *generate_once(int first_iter) {
  char * trash = handler_next(fake_handler);
  return handler_next(handler);
}

void reset_testing(Handler* handler, char** history, size_t size){


  file_handler_reset(handler,pos);
  char* res=file_handler_next(handler);
  munit_assert_string_equal(res, history[pos]);
}

void assert_handler_generic_iteration_test(Handler *the_handler, Handler *the_fake_handler,
                                           size_t expected_cycle_size) { // fake handler is a same type handler to trap board effect bugs inside handler classes
  handler = the_handler;
  fake_handler = the_fake_handler;
  
  munit_assert_size(expected_cycle_size ,==, handler_size(the_handler));

  char** history = assert_iteration_test(generate_once, expected_cycle_size);
  
  reset_testing(handler, history);

  handler_free(handler);
  handler_free(fake_handler);
}
