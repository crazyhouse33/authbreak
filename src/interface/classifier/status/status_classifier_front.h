#include "backend_operators.h"
#include "enum.h"
#define XX_status_OPERATOR(XX) \
    XX(status_inferior_or_eq, "<=",= inferior_or_eq) \
    XX(status_inferior_strict,"<",= inferior_strict) \
    XX(status_superior_or_eq, ">=",= superior_or_eq) \
    XX(status_superior_strict, ">",= superior_strict) \
    XX(status_equal,"==",= equal) \
    XX(status_not_equal,"!=",= not_equal) 


DECLARE_ENUM(Supported_status_operator,XX_status_OPERATOR);

int parse_status_classifier_str_value(char* status_str);
/*Parse a string as a status classifier string and return appropirate int 
 *
 * A status string is an int 
 * */
