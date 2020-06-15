#ifndef XX_GUARD_COMPOSED_CLASSIFIER_H__X
#define XX_GUARD_COMPOSED_CLASSIFIER_H__X
#include "output.h"
#include <stdbool.h>
#include "strcmp_classifier.h"
#include "time_classifier.h"
// After coding the polymoprhysm stuff, I realized it's really not worth all of that complex switching. Keeping track of every instance of each separate structure is not more messy in my opinion, and remove every switching. I am going to try this aproach with maccro base polymorhpism unstead



typedef struct Composed_classifier{
	Classifier_stringcmp* stringcmp_class;
	size_t num_stringcmp;
	Classifier_time* time_class;
	size_t num_time;
} Composed_classifier;
bool classify_output(Composed_classifier* classifier, Output* out);
/*Apply each condition of the classifier to classify an output as success or failure*/
#endif
