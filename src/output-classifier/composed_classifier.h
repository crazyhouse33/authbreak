
// After coding the polymoprhysm stuff, I realized it's really not worth all of that complex switching. Keeping track of every instance of each separate structure is not more messy in my opinion, and remove every switching. I am going to try this aproach with maccro base polymorhpism unstead


typedef struct composed_classifier{
	Classifier_strcmp** and_stringcmp;
	Classifier_strcmp** or_stringcmp;
	Classifier_time** and_time;
	Classifier_time** or_time;
} Handler_options;





