#include "enum.h"
#include "backend_operators.h"

#define XX_time_OPERATOR(XX) \
    XX(time_inferior_or_eq,"<=",=inferior_or_eq) \
    XX(time_inferior_strict,"<",=inferior_strict) \
    XX(time_superior_or_eq,">=",=superior_or_eq) \
    XX(time_superior_strict,">",=superior_strict) \


DECLARE_ENUM(Supported_time_operator,XX_time_OPERATOR);

 int parse_time_classifier_str_value(char* time_str);
/*Parse a string as a time classifier string and return according value 
 *
 * A time classifier string value is an int
 * */


