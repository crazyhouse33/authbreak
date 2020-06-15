#ifndef XX_GUARD_STRCMP_CLASSIFIER_XX
#define XX_GUARD_STRCMP_CLASSIFIER_XX
#include "enum.h"
#include "classifier_common.h"
#include "output.h"

#define XX_stringcmp_OPERATOR(XX) \
    XX(equal,"==",)\
    XX(not_equal,"!=",)

DECLARE_ENUM(Supported_stringcmp_operator,XX_stringcmp_OPERATOR);
typedef struct Classifier_stringcmp{
	Classifier_common common;
	char* target_string;
}Classifier_stringcmp;


//heritating classiffier functions
#define STRCMP_INIT_SIGNATURE(XX) \
	XX(char*, target_str)

HERITATE_CLASSIFIER_DECLARATION(stringcmp, STRCMP_INIT_SIGNATURE);
#endif
