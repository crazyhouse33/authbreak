#include "composed_classifier.h"
#include "classifier_common.h"

#define CLASSIFY(type)                                                                                                                                                                                 \
  for (int i = 0; i < classifier->num_##type; i++)                                                                                                                                                     \
    if (!Classifier_##type##_classify(&classifier->type##_class[i], out))                                                                                                                              \
  return false

bool classify_output(Composed_classifier *classifier, Output *out) {
  CLASSIFY(strcmp);
  CLASSIFY(time);
  return true;
}
