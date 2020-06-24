#include "strcmp_classifier.h"
#include "classifier_common.h"
#include "backend_operators.h"
#include "string.h"


void classifier_stringcmp_init_core_value(Classifier_stringcmp *class, char *target) { class->target_string = target; }

void classifier_stringcmp_init_core_op(Classifier_stringcmp *class, Operator op) {
	switch (op){
		case equal:
			break;
		case not_equal:
			class->common.target= ! class->common.target;
		break;
	}
}

bool classifier_stringcmp_classify_core(Classifier_stringcmp *classifier, char* target) { return strcmp(classifier->target_string, target) == 0; }

HERITATE_CLASSIFIER_DEFINITION(stringcmp, char*); // heriting mother function
