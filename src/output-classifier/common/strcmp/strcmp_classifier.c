#include "strcmp_classifier.h"
#include "classifier_common.h"
#include "string.h"

void stringcmp_init_core(Classifier_stringcmp *class, char *target) { class->target_string = target; }

bool stringcmp_classify_core(Classifier_stringcmp *classifier, Output *output) { return strcmp(classifier->target_string, output->out) == 0; }

HERITATE_CLASSIFIER_DEFINITION(stringcmp, STRCMP_INIT_SIGN); // heriting mother function
