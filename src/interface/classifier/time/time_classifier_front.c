#include "time_classifier_front.h"
#include "error.h"
#include "string.h"
#include "trim_string.h"
void parse_time_classifier_str(Classifier_time *classifier, char *time_str) {
  char *op_end;
  Supported_operator op = str_to_Supported_operator_no_fail_flexible(time_str, 2, &op_end);
  op_end++;
  char *valid_end;
  long int target = strtol(op_end, &valid_end, 0);

  if (target < 0 && *valid_end)
    controlled_error_msg(2, "Parsing Error: Specified time classifier target \"%s\" is not a valid, please put a positive integer", time_str);

  time_init_core(classifier, (int)target, op);
}
