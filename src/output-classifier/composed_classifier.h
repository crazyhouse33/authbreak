#ifndef XX_GUARD_COMPOSED_CLASSIFIER_H__X
#define XX_GUARD_COMPOSED_CLASSIFIER_H__X
#include "output.h"
#include <stdbool.h>
#include <stdlib.h>//calloc and realloc
#include "strcmp_classifier.h"
#include "eq_int_classifier.h"
#include "diff_long_classifier.h"
#include "diff_int_classifier.h"
// After coding the polymoprhysm stuff, I realized it's really not worth all of that complex switching. Keeping track of every instance of each separate structure is not more messy in my opinion, and remove every switching. I am going to try this aproach with maccro base polymorhpism unstead

//TODO list types and names once in a xmaccro and use it unstead

#define TYPE(type, name) \
	Classifier_##type* name##_class;\
	size_t num_##name


typedef struct Composed_classifier{
	bool target;
	TYPE(stringcmp, stringcmp);
	TYPE(diff_long, time);
	TYPE(diff_int, status_diff);
	TYPE(eq_int, status_eq);
} Composed_classifier;
bool composed_classifier_classify_output(Composed_classifier* classifier, Output* out);
/*Apply each condition of the classifier to classify an output as success or failure*/

Composed_classifier* composed_classifier_new(bool target);
/*Create empty classifier*/

#endif
