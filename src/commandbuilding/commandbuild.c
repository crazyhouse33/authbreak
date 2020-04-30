#include "commandbuild.h"
#include "argv.h"
#include "handler.h"
#include "null_vec.h"
#include "replace_string.h"


//TODO Dont use pointer for less cache miss and deferences
typedef struct Template_unit {
	Placeholder* placeholder;
	Handler* handler;
} Template_unit;

//Fix state
Template_unit* templates; // Couple of handler, placeholder
size_t unit_num;//number of couple

char **argv;//The result

//Dynamic state
long unsigned int iterator;//used for sessionning


/*This file is important optimization wise because it's the only real cpu work that will do the process for the brutforce part*/




void prepare_command_builder(char *command, char **prompts) {
  /*Gather all the templates, assign handlers, prepare the fix part, also check if session allready exist to continue it unstead of creating new one*/
  size_t command_size;
  argv = arg_vector_from_string(command, &command_size);
  char *sub_part = *argv;
  Placeholder** placeholders= (Placeholder**)create_vector(0);
  // Getting every placeholders
  while (sub_part++ != NULL) {
    Placeholder **new_placeholders = placeholder_parse_string(sub_part, '{', '}', '\\');
    unit_num = concatenate_vector((void ***)&placeholders, (void **)new_placeholders);
  }

  //Setting the switching units
  templates= malloc(sizeof(Template_unit)* unit_num);
  for (size_t i=0 ; i< unit_num; i++){
	  templates[i].placeholder = placeholders[i];
	  templates[i].handler = NULL; // TODO // Create appropriate handler

   
  } 

}

//TODO do a sneaky cartesian product along with furtivity option (change order to have change in each consecutive template
bool command_builder_next_command(){//Cartesian product
	Template_unit* current_template= templates;
	char* next_value=handler_next(current_template->handler); 
	while (! next_value){//the handler is done
		handler_reset(current_template->handler);
		current_template++;
		if (current_template -templates > unit_num)//everything had been done
			return true;
		next_value= handler_next(current_template->handler);
	}
	placeholder_switch(current_template->placeholder, next_value ); 
	iterator++;
	return false;
}


void command_builder_fix(size_t positions, char *fix);

char *command_builder_serialize();
/*Serialize the state*/

void *command_builder_unserialize(char *string);
/*Set the state as specified in string*/
