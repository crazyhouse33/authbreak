#include "output_classifier_front.h"
#include "handler_front.h" //We reuse handler key based option parsing
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

#define CASE(type)                                                                                                                                                                                     \
  case type:                                                                                                                                                                                           \
    classifier->type##_class[classifier->num_##type].common.target = !must_be_false;                                                                                                                   \
    parse_##type##_classifier_str(&classifier->type##_class[classifier->num_##type++], value);                                                                                                         \
    break

Authorized_classifier_type_key parse_classifier_str(Composed_classifier *classifier, char *classifier_str) {
  bool must_be_false = (*classifier_str == '!');
  if (must_be_false) { // we trim after, we dont actualize the value size because it's not used in the classifier parsing
    classifier_str++;
    left_trim(classifier_str);
  }
  size_t size = strlen(classifier_str);
  char *value;
  char *key;

  size_t value_size;
  size_t key_size;

  handler_separate_option(classifier_str, size, &key, &value, &key_size, &value_size);

  Authorized_classifier_type_key type = str_to_Authorized_classifier_type_key_no_fail(key, key_size);
  switch (type) {
    CASE(stringcmp);
    CASE(time);
  }
  return type;
}
