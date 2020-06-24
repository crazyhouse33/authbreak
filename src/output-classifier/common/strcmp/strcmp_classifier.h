#include "enum.h"
#include "classifier_common.h"
#include "output.h"

typedef struct Classifier_stringcmp{
	Classifier_common common;
	char* target_string;
}Classifier_stringcmp;


HERITATE_CLASSIFIER_DECLARATION(stringcmp, char* );
