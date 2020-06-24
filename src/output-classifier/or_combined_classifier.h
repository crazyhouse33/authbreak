#ifndef XX_GUARD_OR_COMBINED_CLASSIFIER__XX
#define XX_GUARD_OR_COMBINED_CLASSIFIER__XX
#include "composed_classifier.h"
#include <stdlib.h>
// After coding the polymoprhysm stuff, I realized it's really not worth all of that complex switching. Keeping track of every instance of each separate structure is not more messy in my opinion, and remove every switching. I am going to try this aproach with maccro base polymorhpism unstead



typedef struct Or_combined_classifier{
	size_t num_groups;
	Composed_classifier* groups;
} Or_combined_classifier;
bool or_combined_classifier_classify_output(Or_combined_classifier* classifier, Output* out);
/*Return true if one of the classifiers group is true*/


void or_combined_classifier_add(Or_combined_classifier* group_class, Composed_classifier* class);



Or_combined_classifier* or_combined_classifier_new();

#endif
