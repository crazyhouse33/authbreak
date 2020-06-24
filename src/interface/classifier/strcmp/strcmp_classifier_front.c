#include "strcmp_classifier_front.h"

DEFINE_ENUM(Supported_stringcmp_operator, "\"%s\" is not a suported operator for out_eq classifier, chose amongs this options: \n%s\n", "\"%s\" is ambigious as an out_eq operator, choose among: \n%s\n", XX_stringcmp_OPERATOR);\

/*Parse a string as a time classifier string and return appropiate value*/
char* parse_stringcmp_classifier_str_value(char *strcmp_str) { return strcmp_str; }


