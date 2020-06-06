#include "strcmp_classifier_front.h"
/*Parse a string as a time classifier string and set classifier accordingly*/
void parse_stringcmp_classifier_str(Classifier_stringcmp* classifier,char* strcmp_str){
stringcmp_init_core(classifier, strcmp_str);
}
