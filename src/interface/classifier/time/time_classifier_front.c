#include "time_classifier_front.h"
#include "error.h"
#include "string.h"
#include "trim_string.h"
int parse_time_classifier_str_value(char *time_str) {
	char* valid_end;
  long int target = strtol(time_str, &valid_end, 0);

  if (target < 0 && *valid_end)
    controlled_error_msg(2, "Parsing Error: Specified time classifier value \"%s\" is not a valid, please put a positive integer", time_str);

  return (int) target;
}
