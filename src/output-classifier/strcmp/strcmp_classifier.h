#include "classifier_common.h"
#include "output.h"
typedef struct Classifier_strcmp{
	Classifier_common common;
	char* target_string;
}Classifier_strcmp;


//heritating classiffier functions
#define STRCMP_INIT_SIGN(XX) \
	XX(char*, target_str)

HERITATE_CLASSIFIER_DECLARATION(strcmp, STRCMP_INIT_SIGN);
