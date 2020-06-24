#include "backend_operators.h"
#include "enum.h"

#define XX_stringcmp_OPERATOR(XX) \
    XX(strcmp_equal,"==",=equal) \
    XX(strcmp_not_equal,"!=",=not_equal)

DECLARE_ENUM(Supported_stringcmp_operator,XX_stringcmp_OPERATOR);


char* parse_stringcmp_classifier_str_value(char* strcmp_str);
/*Parse a string as a strcmp classifier string and et classifier accordingly
 *
 * A strcmp string is a string to be equal to the output
 * */
