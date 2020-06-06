#include "enum.h"
#include "error.h"
#include "search_string.h"//SEARCH_ERROR_MATCHS_AMBIGUITY

ssize_t __enum_str_conversion_error_filter(ssize_t error, char* format_NOMATCH, char* format_AMBIGIOUS,char* value, char** match_list){
	switch (error){
		case SEARCH_ERROR_NO_MATCH:
			controlled_error_msg(2,format_NOMATCH, value, join_argv(match_list,'\n'));
			break;
		case SEARCH_ERROR_MATCHS_AMBIGUITY:
			controlled_error_msg(2,format_AMBIGIOUS, value, join_argv(match_list, '\n'));
			break;
	}
	return error;
}
