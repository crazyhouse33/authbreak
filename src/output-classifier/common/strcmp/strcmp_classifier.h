#ifndef XX_GUARD_STRCMP_CLASSIFIER_XX
#define XX_GUARD_STRCMP_CLASSIFIER_XX
#include "classifier_common.h"
#include "output.h"
typedef struct Classifier_stringcmp{
	Classifier_common common;
	char* target_string;
}Classifier_stringcmp;


//heritating classiffier functions
#define STRCMP_INIT_SIGN(XX) \
	XX(char*, target_str)

HERITATE_CLASSIFIER_DECLARATION(stringcmp, STRCMP_INIT_SIGN);
#endif
