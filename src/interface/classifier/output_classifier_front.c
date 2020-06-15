#include "output_classifier_front.h"
#include "string.h"
#include "trim_string.h"

#include "strcmp_classifier_front.h"
#include "time_classifier_front.h"

#define ERROR_STR_OPT_NO_MATCH "Sucess classifier key \"%s\" is not valid, chose among the following:\n%s\n"
#define ERROR_STR_OPT_AMBIGIOUS "Sucess classifier key %s is ambigious, choose among:\n%s\n"

DEFINE_ENUM(Authorized_classifier_type_key, ERROR_STR_OPT_NO_MATCH, ERROR_STR_OPT_AMBIGIOUS, AUTHORIZED_CLASSIFIER);

// dispatcher:

// Note that we finally dont use the generic _init for each classifier, because it would need to gather classifier specific stuff as return value for each one of them. By calling direct side effect
// parsing we avoid the problem

#define CASE_PARSE_OP(type) \
	case type:\
		*class_op= str_to_Supported_##type##_operator_no_fail_flexible(end, 2,&end);\
	break


//Its not static for testing
Authorized_classifier_type_key classifier_separate_classifier( char *class_string, size_t until, char **class_value, size_t *value_size, int* class_op){
	char* end;
	Authorized_classifier_type_key type = str_to_Authorized_classifier_type_key_no_fail_flexible(class_string, MAX_SIZE_AUTHORIZED_CLASSIFIER, &end);
	end++;
	left_trim_in_place(&end);
	
	switch (type){
		CASE_PARSE_OP(stringcmp);
		CASE_PARSE_OP(time);
	}
	end++;
	left_trim_in_place(&end);
	*class_value=end;
	*value_size=class_string+until-end;
	return type;
}

#define CASE_INIT(type)\
  case type:\
    classifier->type##_class[classifier->num_##type].common.target = !must_be_false;\
    classifier_##type##_init_core_op(&classifier->type##_class[classifier->num_##type], class_op);\
    classifier_##type##_init_core_value(&classifier->type##_class[classifier->num_##type++], parse_##type##_classifier_str_value(class_value));\
    break

Authorized_classifier_type_key parse_classifier_str(Composed_classifier *classifier, char *classifier_str) {
  bool must_be_false = (*classifier_str == '!');
  if (must_be_false) { // we trim after, we dont actualize the value size because it's not used in the classifier parsing
    classifier_str++;
    left_trim_in_place(&classifier_str);
  }
  size_t size = strlen(classifier_str);
  int class_type;
  char *class_value; 
  size_t value_size;
  int class_op;
  Authorized_classifier_type_key type = classifier_separate_classifier(classifier_str, size, &class_value, &value_size, &class_op);


  switch (type) {
    CASE_INIT(stringcmp);
    CASE_INIT(time);
  }
  return type;
}
