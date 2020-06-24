#include "backend_operators.h"
#include "classifier_common.h"
#include <stdbool.h>
//This is templated basic classifier, that you can use whatever the numerical type you want


#define DECLARE_DIFF_NUM(type) \
typedef struct Classifier_diff_##type {\
	Classifier_common common;\
	signed type target;\
	signed type adder;\
	signed type multiplier;\
}Classifier_diff_##type;\
bool classifier_diff_##type##_classify_core(Classifier_diff_##type* classifier, type to_classify);\
void classifier_diff_##type##_init_core_op(Classifier_diff_##type* classifier, Operator);\
void classifier_diff_##type##_init_core_value(Classifier_diff_##type* classifier, type target);\
HERITATE_CLASSIFIER_DECLARATION(diff_##type, type );


#define DEFINE_DIFF_NUM(type) \
bool classifier_diff_##type##_classify_core(Classifier_diff_##type* classifier, type to_classify){\
return (classifier->multiplier * to_classify) < (classifier->multiplier * (classifier->target + classifier->adder));\
}\
void classifier_diff_##type##_init_core_op(Classifier_diff_##type *classifier, Operator op) {\
  switch (op) {\
  case inferior_strict:\
    classifier->adder = 0;\
    classifier->multiplier = 1;\
    break;\
  case inferior_or_eq:\
    classifier->adder = 1;\
    classifier->multiplier = 1;\
    break;\
  case superior_strict:\
    classifier->adder = 0;\
    classifier->multiplier = -1;\
    break;\
  case superior_or_eq:\
    classifier->adder = -1;\
    classifier->multiplier = -1;\
    break;\
  }\
}\
void classifier_diff_##type##_init_core_value(Classifier_diff_##type* classifier, type target){\
	classifier->target = (signed) target;\
}\
HERITATE_CLASSIFIER_DEFINITION(diff_##type, type);





