#include "time_classifier_front.h"
#include "search_string.h"

DEFINE_ENUM(Supported_time_operator, "\"%s\" is not a suported operator for time classifier, chose amongs this options: \n%s\n", "\"%s\" is ambigious as an operator, choose among: \n%s\n", XX_time_OPERATOR);

int parse_time_classifier_str_value(char *time_str) {
	return parse_positive_int_intolerant(time_str, 2, "Parsing Error: Specified time classifier value \"%s\" is not a valid, please put a positive integer");

}


