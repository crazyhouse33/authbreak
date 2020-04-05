
typedef struct Handler
{
char* main_component;
Dict options;
int (*getValues)();// For each different kind of handler, getValues is going to be different
unsigned int _buffer_size;

} Handler;

Handler Handler_get(main_component, options);
/*Handler constructor, prepare some default values and set the getValues function acording to the nature of main component*/

char* Handler_get_next_value(Handler handler);
/*Return next value for the template*/

void Handler_skip_values(unsigned int n);
/*Skip the n next values*/
