#ifndef XX__CLASSIFIER_COMMON__XX_GUARD
#define XX__CLASSIFIER_COMMON__XX_GUARD
#include <stdbool.h>
#include "backend_operators.h"
typedef struct Classifier_common{
		bool target;//The classifier must be true/false
}Classifier_common;

void classifier_init_classifier_common(Classifier_common* classifier, bool target);


//maccro based polymorphism. You can read some article about the advantages of using such methods, mainely it's for performance reason (two times faster than using void* approach such as what I did with handler, and this also dont include the cost of branching)
//This is equivalent to copy past the same functionnement for every subclass but without the maintenability drawback


#define HERITATE_CLASSIFIER_DEFINITION(classfier_type, target_type)\
bool classifier_##classfier_type##_classify(Classifier_##classfier_type* classfier,  target_type out){\
	return classifier_##classfier_type##_classify_core( classfier, out) ==classfier->common.target;\
	}\
void classifier_##classfier_type##_init(Classifier_##classfier_type* classfier, bool target,  Operator op, target_type target_value){\
	classifier_init_classifier_common(&classfier->common, target);\
	classifier_##classfier_type##_init_core_op(classfier, op);\
	classifier_##classfier_type##_init_core_value(classfier, target_value);\
}


#define HERITATE_CLASSIFIER_DECLARATION(classfier_type,target_type)\
bool classifier_##classfier_type##_classify(Classifier_##classfier_type* classfier, target_type out);\
void classifier_##classfier_type##_init(Classifier_##classfier_type* classfier, bool target, Operator op, target_type target_value);\
void classifier_##classfier_type##_init_core_value(Classifier_##classfier_type* classfier, target_type target);\
void classifier_##classfier_type##_init_core_op(Classifier_##classfier_type* classfier, Operator op);

#endif
