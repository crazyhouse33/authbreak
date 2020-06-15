#ifndef XX__CLASSIFIER_COMMON__XX_GUARD
#define XX__CLASSIFIER_COMMON__XX_GUARD
#include <stdbool.h>
typedef struct Classifier_common{
		bool target;//The classifier must be true/false
}Classifier_common;

void classifier_init_classifier_common(Classifier_common* classifier, bool target);


//maccro based polymorphism. You can read some article about the advantages of using such methods, mainely it's for performance reason (two times faster than using void* approach such as what I did with handler, and this also dont include the cost of branching)
//This is equivalent to copy past the same functionnement for every subclass but without the maintenability drawback

#define GET_WHOLE(type, id) type id
#define GET_ID(type, id) id

#define HERITATE_CLASSIFIER_DEFINITION(classfier_type,XMACRO)\
bool Classifier_##classfier_type##_classify(Classifier_##classfier_type* classfier, Output* out){\
	return classifier_##classfier_type##_classify_core( classfier, out) ==classfier->common.target;\
	}\
void Classifier_##classfier_type##_init(Classifier_##classfier_type* classfier, bool target, Supported_##classfier_type##_operator op, XMACRO(GET_WHOLE)){\
	classifier_init_classifier_common(&classfier->common, target);\
	classifier_##classfier_type##_init_core_op(classfier, op);\
	classifier_##classfier_type##_init_core_value(classfier, XMACRO(GET_ID));\
}


#define HERITATE_CLASSIFIER_DECLARATION(classfier_type,XMACRO)\
bool Classifier_##classfier_type##_classify(Classifier_##classfier_type* classfier, Output* out);\
void Classifier_##classfier_type##_init(Classifier_##classfier_type* classfier, bool target, Supported_##classfier_type##_operator op, XMACRO(GET_WHOLE));\
void classifier_##classfier_type##_init_core_value(Classifier_##classfier_type* classfier, XMACRO(GET_WHOLE));\
void classifier_##classfier_type##_init_core_op(Classifier_##classfier_type* classfier, Supported_##classfier_type##_operator op);

#endif
