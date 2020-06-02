#include "strcmp_classifier.h"
#include "classifier_common.h"
#include "string.h"

void strcmp_init_core(Classifier_strcmp *class, char *target) { class->target_string = target; }

bool strcmp_classify_core(Classifier_strcmp *classifier, Output *output) { return strcmp(classifier->target_string, output->out) == 0; }

HERITATE_CLASSIFIER_DEFINITION(strcmp, STRCMP_INIT_SIGN); // heriting mother function
