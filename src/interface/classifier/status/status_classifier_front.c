#include "status_classifier_front.h"

DEFINE_ENUM(Supported_status_operator, "\"%s\" is not a suported operator for status classifier, chose amongs this options: \n%s\n", "\"%s\" is ambigious as a status operator, choose among: \n%s\n", XX_status_OPERATOR);

/*Parse a string as a time classifier string and return appropiate value*/
 int parse_status_classifier_str_value(char *strcmp_str) { 
	return parse_int_intolerant(strcmp_str, 2, "Parsing Error: Specified status classifier value \"%s\" is not a valid, please put an integer");
 }
