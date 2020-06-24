#include "backend_operators.h"
#include "classifier_common.h"
//This is templated basic classifier, that you can use whatever the numerical type you want

#define DECLARE_EQUAL_NUM(type) \
typedef struct Classifier_eq_##type {\
	Classifier_common common;\
	signed type target;\
}Classifier_eq_##type;\
bool classifier_eq_##type##_classify_core(Classifier_eq_##type* classifier, type to_classify);\
void classifier_eq_##type##_init_core_op(Classifier_eq_##type* classifier, Operator);\
void classifier_eq_##type##_init_core_value(Classifier_eq_##type* classifier, type target);\
HERITATE_CLASSIFIER_DECLARATION(eq_##type, type )

#define DEFINE_EQUAL_NUM(type) \
bool classifier_eq_##type##_classify_core(Classifier_eq_##type* classifier, type to_classify){\
return (classifier->target == to_classify);\
}\
void classifier_eq_##type##_init_core_op(Classifier_eq_##type *classifier, Operator op) {\
  switch (op){\
		case equal:\
			break;\
		case not_equal:\
			classifier->common.target= ! classifier->common.target;\
		break;\
	}\
}\
void classifier_eq_##type##_init_core_value(Classifier_eq_##type* classifier, type target){\
	classifier->target =  target;\
}\
HERITATE_CLASSIFIER_DEFINITION(eq_##type, type)








