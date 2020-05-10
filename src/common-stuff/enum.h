/*Define some magic enum macro, this just assume enum are contigious by default, if you find a compiler for which this is not the case, write an issue and I will change the code to supress this assumption, by adding a normal array containg every enum, and looping on it's normal int index rather than ++enum */

#define GET_FIRST_ARG(first, ...) first

//We also recuperate first first enum value in case of weird implemenation

#define CREATE_ENUM(name, ...)\
typedef enum name {__VA_ARGS__} name;\
name name##_first_INTERNAL_ENUM = GET_FIRST_ARG(__VA_ARGS__)

#define ASSOCIATE_E(name, ...)\
char*  name##_parsing_str[]={__VA_ARGS__,NULL}; \
bool str_to_##name(char* value, size_t until, name* result) {\
	Handler_type cpt = name##_first_INTERNAL_ENUM;\
	char* current;\
	while ( current = name##_parsing_str[cpt]){\
		if ( ! strncmp(value, current, until)){\
			*result = cpt;\
			return true;\
		}\
		cpt++;\
	}\
	return false;\
}


