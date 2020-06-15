#ifndef XX_TIME_CLASSIFIER_XX_GUARD
#define XX_TIME_CLASSIFIER_XX_GUARD
#include "classifier_common.h"
#include "output.h"
#include "enum.h"
//This morally should be elsewhere, but we dont need it elsewhere yet
#define XX_time_OPERATOR(XX) \
    XX(inferior_or_eq,"<=",) \
    XX(inferior_strict,"<",) \
    XX(superior_or_eq,">=",) \
    XX(superior_strict,">",) \

DECLARE_ENUM(Supported_time_operator,XX_time_OPERATOR);

typedef struct Classifier_time{
	Classifier_common common;
	int target_int;

	//Resolve operator stuff without branching
	//we add 1 if user want strict comparison and multpily by -1 if he want superior unstead of inferior
	int multiplier;
	int adder;

}Classifier_time;


//heritating classiffier functions
#define TIME_INIT_SIGNATURE(XX) \
	XX(int, target_int)\

HERITATE_CLASSIFIER_DECLARATION(time, TIME_INIT_SIGNATURE);
#endif
