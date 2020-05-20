#include <sys/types.h>//size_t
#include <stdbool.h>
#include "search_string.h"//get_uniq
#include "macro_util.h"// macro_narg
#include "error.h"
# include "argv.h"//join_argv

// expansion macro for enum value definition
#define ENUM_VALUE(name,repr, assign) name assign,

#define ENUM_NAME(name, repr, assign) name,
#define ENUM_NAME_STRING(name, repr, assign) repr,

/// declare the access function and define enum values
#define DECLARE_ENUM(name,ENUM_DEF) \
  typedef enum name { \
    ENUM_DEF(ENUM_VALUE) \
  } name; \
  char* name##_to_str(name the_name);\
  size_t get_##name##_number();\
  name * get_##name##_iterator();\
  bool str_to_##name( char* value, size_t until, name* res);\
  name str_to_##name##_no_fail(char* value, size_t until)

/// define the access function names
#define DEFINE_ENUM(name,format_NOMATCH, format_AMBIGIOUS, ENUM_DEF) \
	name name##_enum_iterator[]= {ENUM_DEF(ENUM_NAME)};\
	name * get_##name##_iterator(){\
		return name##_enum_iterator;\
	}\
	char** name##_parsing_str=(char* []){ENUM_DEF(ENUM_NAME_STRING) NULL}; \
	bool str_to_##name(char* value, size_t until, name* res){\
		ssize_t cpt = get_unique_matching_string(name##_parsing_str, value, until);\
		if (cpt <0)\
		return false;\
		*res= name##_enum_iterator[cpt];\
		return true;\
	}\
	name str_to_##name##_no_fail(char* value, size_t until) {\
		ssize_t cpt = get_unique_matching_string(name##_parsing_str, value, until);\
		switch (cpt){\
			case SEARCH_ERROR_NO_MATCH:\
						   controlled_error_msg(2,format_NOMATCH, value, join_argv(name##_parsing_str,'\n'));\
			break;\
			case SEARCH_ERROR_MATCHS_AMBIGUITY:\
							   controlled_error_msg(2,format_AMBIGIOUS, value, join_argv(name##_parsing_str, '\n'));\
			break;\
			default:\
				return name##_enum_iterator[cpt];\
		}\
	}\
	char* name##_to_str(name the_name){\
		return name##_parsing_str[the_name];\
	}\
	size_t name##_enum_iterator_size = MACRO_N_ARG(ENUM_DEF(ENUM_NAME))-1;\
	size_t get_##name##_number(){\
		return  name##_enum_iterator_size;\
	}
	 
//Note the -1 because we always put an useless coma
