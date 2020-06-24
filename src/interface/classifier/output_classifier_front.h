#include "composed_classifier.h" //classifier backend

#define MAX_SIZE_AUTHORIZED_CLASSIFIER 6
#define AUTHORIZED_CLASSIFIER(XX)\
	XX(stringcmp,"out_eq",)\
	XX(time,"time",)\
	XX(status,"status",)

DECLARE_ENUM(Authorized_classifier_type_key,AUTHORIZED_CLASSIFIER);

Authorized_classifier_type_key parse_classifier_str(Composed_classifier* classifier, char* classifier_str);
/*Parse a string and add matching classifier backend to the specified composed classifier at specified position. Return the elected type as well*/
