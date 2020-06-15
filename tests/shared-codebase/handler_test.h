#include "handler.h"
#include <stddef.h>//size_t

void assert_handler_generic_iteration_test(Handler* handler, Handler* fake_handler, size_t expected_cycle);
/*Test that the handler produce cycle contening the expected amout of uniq value. Fake handler is used in betwen true handler iteration to check board effect of handler implementation*/
