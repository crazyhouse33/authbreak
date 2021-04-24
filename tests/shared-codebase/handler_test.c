#include "handler.h"
#include "munit.h"
#include "test_unicity.h"
#include "fast_rand.h"

Handler *handler;
Handler *fake_handler;

char *generate_once(int first_iter) {
	char * trash = handler_next(fake_handler);
	return handler_next(handler);
}

void reset_testing(Handler* handler, char** history, size_t size){
	fast_rand_seed(21);
	file_handler_reset(handler,pos);
	if (! size)
		return;
	for (int i=0; i<10; i++){
		size_t pos= fast_rand_until(size);
		size_t until= fast_rand_until(size - pos);
		handler_reset(pos);
		for (int j=0; j<until;j++){
			char* res=handler_next(handler);
			munit_assert_string_equal(res, history[pos++]);
		}
	}
}

void assert_handler_generic_iteration_test(Handler *the_handler, Handler *the_fake_handler,
		size_t expected_cycle_size) { // fake handler is a same type handler to trap board effect bugs inside handler classes
	handler = the_handler;
	fake_handler = the_fake_handler;

	munit_assert_size(expected_cycle_size ,==, handler_size(the_handler));

	char** history = assert_iteration_test(generate_once, expected_cycle_size);

	reset_testing(handler, history, expected_cycle_size);

	handler_free(handler);
	handler_free(fake_handler);
}
