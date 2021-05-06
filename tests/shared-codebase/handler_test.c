#include "template.h"
#include "replace_string.h"
#include "munit.h"
#include "test_unicity.h"
#include "fast_rand.h"

Template *template;
Template *fake_template;

Template* mock_template(Handler* handler){
	Template* ret = malloc(sizeof(Template));
	char** point_to_str = malloc(sizeof(char*));
	char* plinit= strdup("{}");
	*point_to_str = plinit;
	Placeholder* pl = placeholder_new(point_to_str,plinit, plinit + strlen(plinit)-1);
	ret->handler=handler;
	ret->placeholder=pl;
	return ret;

}

char *generate_once(int first_iter) {
	char * trash = template_next(fake_template);
	return template_next(template);
}

void reset_testing(Template* template, char** history, size_t size){
	fast_rand_seed(21);
	for (int i=0; i<10; i++){
		size_t pos= fast_rand_until(size);
		size_t until= fast_rand_until(size - pos);
		template_reset_to(template, pos);
		for (int j=0; j<until;j++){
			char* res=template_next(template);
			munit_assert_string_equal(res, history[pos++]);
		}
	}
}

void assert_handler_generic_iteration_test(Handler *the_handler, Handler *the_fake_handler, size_t expected_cycle_size) { 
	// fake handler is a same type handler to trap board effect bugs inside handler classes
	template = mock_template(the_handler);
	fake_template = mock_template(the_fake_handler);

	munit_assert_size(expected_cycle_size ,==, handler_size(the_handler));

	char** history = assert_iteration_test(generate_once, expected_cycle_size);

	reset_testing(template, history, expected_cycle_size);

	template_free(template);
	template_free(fake_template);
}
