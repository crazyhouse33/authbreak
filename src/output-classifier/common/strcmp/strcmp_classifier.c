#include "strcmp_classifier.h"
#include "classifier_common.h"
#include "string.h"


DEFINE_ENUM(Supported_stringcmp_operator, "\"%s\" is not a suported operator for out_eq classifier, chose amongs this options: \n%s\n", "\"%s\" is ambigious as an operator, choose among: \n%s\n", XX_stringcmp_OPERATOR);\
void classifier_stringcmp_init_core_value(Classifier_stringcmp *class, char *target) { class->target_string = target; }

void classifier_stringcmp_init_core_op(Classifier_stringcmp *class, Supported_stringcmp_operator op) {
	switch (op){
		case equal:
			break;
		case not_equal:
			class->common.target= ! class->common.target;
		break;
	}
}

bool classifier_stringcmp_classify_core(Classifier_stringcmp *classifier, Output *output) { return strcmp(classifier->target_string, output->out) == 0; }

HERITATE_CLASSIFIER_DEFINITION(stringcmp, STRCMP_INIT_SIGNATURE); // heriting mother function
