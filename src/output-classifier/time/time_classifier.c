#include "time_classifier.h"
#include "classifier_common.h"

//DEFINE_ENUM(Operator, "\"%s\" is not a suported operator, chose amongs this options: \n%s\n", "\"%s\" is ambigious as an operator, choose among: \n%s\n", OPERATOR);

void time_init_core(Classifier_time* classifier, int target_int, Operator op){
	classifier->target_int=target_int;
	switch (op){
		case inferior_strict:
			classifier->adder=0;
			classifier->multiplier=1;
			break;
		case inferior_or_eq:
			classifier->adder=1;
			classifier->multiplier=1;
			break;
		case superior_strict:
			classifier->adder=0;
			classifier->multiplier=-1;
			break;
		case superior_or_eq:
			classifier->adder=-1;
			classifier->multiplier=-1;
			break;
	}
}

bool time_classify_core(Classifier_time* classifier, Output* output){
	return (classifier->multiplier * output->term_time)  < (classifier->multiplier * (classifier->target_int+ classifier->adder)); 
}

//heritating mother class
HERITATE_CLASSIFIER_DEFINITION(time, TIME_INIT_SIGN);
