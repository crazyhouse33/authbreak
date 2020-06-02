#include "classifier_common.h"
#include "output.h"
#include "enum.h"
//This morally should be elsewhere, but we dont need it elsewhere yet
#define OPERATOR(XX) \
    XX(inferior_or_eq,"<=",) \
    XX(inferior_strict,"<",) \
    XX(superior_or_eq,">=",) \
    XX(superior_strict,">",) \

DECLARE_ENUM(Operator,OPERATOR);

typedef struct Classifier_time{
	Classifier_common common;
	int target_int;

	//Resolve operator stuff without branching
	//we add 1 if user want strict comparison and multpily by -1 if he want superior unstead of inferior
	int multiplier;
	int adder;

}Classifier_time;


//heritating classiffier functions
#define TIME_INIT_SIGN(XX) \
	XX(int, target_int),\
	XX(Operator, op)

HERITATE_CLASSIFIER_DECLARATION(time, TIME_INIT_SIGN);


