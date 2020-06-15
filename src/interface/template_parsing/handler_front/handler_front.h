#include "handler.h" // include handlers options defined by the backend
#include "enum.h"


//here we define authorized options keys for each handlers

#define AUTHORIZED_FILE(XX) \
    XX(separator,"separator",) \
    XX(charset,"charset",) \
    XX(type,"type",) \

DECLARE_ENUM(Authorized_file_option_key,AUTHORIZED_FILE);

#define AUTHORIZED_ITERATOR(XX) \
    XX(charset_it, "charset",= charset) \
    XX(type_it, "type",=type) \

DECLARE_ENUM(Authorized_iterator_option_key,AUTHORIZED_ITERATOR);




bool handler_parse_main_component(Handler* handler, Handler_type type, char* main, size_t until);
/*Parse main component while interpreting it as a type the entered type, and set handler accordingly. If the parsing does not make sense (IE the acquired value would crash the program after (non existing file, non numerical len...), return false and let handler inchanged
 * */
//TODO LOG the reasonning behind such an automatic choice somewhere if verbosity level is hight enought


void handler_parse_option(Handler *handler, char* opt_begin, size_t until);
/*Parse an option string of a template, such as charset="ab".  THE HANDLER TYPE MUST BE DETERMINED BEFOREHAND. The start and end of string are parsed even if space (not trimmed)*/


void handler_set_default(Handler* handler);
/*Set handler to default values*/

void handler_separate_option(char* option, size_t until, char**key, char** value, size_t *key_size, size_t* value_size);
	/*Take an option bloc wich is something among "  key =   value  ", and set the given pointer to reflect the situation correctely (trim spaces)*/


