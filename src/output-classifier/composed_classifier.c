#include "composed_classifier.h"
#include "classifier_common.h"

#define CLASSIFY(type)                                                                                                                                                                                 \
  for (int i = 0; i < classifier->num_##type; i++)                                                                                                                                                     \
    if (!Classifier_##type##_classify(&classifier->type##_class[i], out))                                                                                                                              \
      return false;

// TODO do a X maccro that call Classify on any type defined on the allready defined enum authorized classifier type , and construct the return statement, so no possible messup is ever possible (like
// forgetting one of those)
bool classify_output(Composed_classifier *classifier, Output *out) {
  CLASSIFY(stringcmp);
  CLASSIFY(time);
  return classifier->num_stringcmp != 0 || classifier->num_time != 0; // if there where no classifier in the first place, it's counted as fail
}
