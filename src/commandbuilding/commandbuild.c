#include "commandbuild.h"
#include "argv.h"
#include "concat_string.h"
#include "handler.h" //Handler
#include "max.h"
#include "null_vec.h"       //concatenate_vector
#include "replace_string.h" //Placeholder

void command_builder_init(Command_builder* builder, char* command, char** prompts){
	builder->templates= (Template**) create_vector(0);
	builder->cartesian_it= 0;
	builder->templates_num = 0;

	size_t command_size;
	builder->argv = arg_vector_from_string(command, &command_size);
	builder->prompts = prompts;

	// Getting every templates 
	size_t it = 0;
	size_t placeholder_num;

	while (builder->argv[it]) {
		Placeholder ** new_placeholders = placeholder_parse_string(&builder->argv[it++], '{', '}', '\\', &placeholder_num);
		for (int i=0; i<placeholder_num;i++){
			Template* template= template_new(new_placeholders[i]);
			put_vector((void***) &builder->templates, (void*)template);
		}
		builder->templates_num+= placeholder_num;
	}
	it = 0;
	while (builder->prompts[it]) {
		builder->prompts[it]=get_concatenation_char(builder->prompts[it],'\n');//Need copy to not segfault
		Placeholder **new_placeholders = placeholder_parse_string(&builder->prompts[it++], '{', '}', '\\', &placeholder_num);
		for (int i=0; i<placeholder_num;i++){
			Template* template= template_new(new_placeholders[i]);
			put_vector((void***) &builder->templates, (void*)template);
		}
		builder->templates_num+= placeholder_num;
	}

}

Command_builder* command_builder_new( char *command, char **prompts) {

	Command_builder* builder = malloc (sizeof(Command_builder));
	command_builder_init(builder, command, prompts);

	return builder;
}

// TODO do a sneaky cartesian product along with furtivity option (change order to have change in each consecutive template
bool command_builder_next_command(Command_builder* builder) { // Cartesian product
	Template** cartesian_cursor = builder->templates + builder->cartesian_it;
	bool blocked_up = template_next(*cartesian_cursor);
	while (blocked_up) { 
		cartesian_cursor++;
		if (cartesian_cursor - builder->templates >= builder->templates_num ) // everything had been done
			return true;
		blocked_up = template_next(*cartesian_cursor);
	}
	return false;
}

char *command_builder_current_command(Command_builder* builder) {
	char *command = join_argv(builder->argv, ' ');
	char *prompts = join_argv(builder->prompts, '\n');
	concat_string(&command, "\n");
	concat_string(&command, prompts);
	free(prompts);
	return command;
}

void command_builder_fix(Command_builder* builder,size_t positions, char *fix);

char *command_builder_serialize(Command_builder* builder);
/*Serialize the state*/

void *command_builder_unserialize(Command_builder* builder, char *string);
/*Set the state as specified in string*/
