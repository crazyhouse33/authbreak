#include "pgcd.h" 
#include "commandbuild_sneaky.h"

static unsigned int* sneaky_command_builder_get_templates_sizes(){

}

Sneaky_command_builder* sneaky_command_builder_new( char *command, char **prompts) {
	Sneaky_command_builder* builder = malloc(sizeof(Sneaky_command_builder));
	command_builder_init(&builder->builder, command, prompts);

	size_t* ghost_sizes = malloc(sizeof(size_t) * builder->builder.templates_num);
	size_t* sizes = malloc(sizeof(size_t) * builder->builder.templates_num);

	for (int i=0; i<builder->builder.templates_num; i++){
		size_t size_i = template_size(builder->builder.templates[i]);
		ghost_sizes[i]=size_i;
		sizes[i]=size_i;
	}
	builder->sizes= sizes;
	make_prime_together(ghost_sizes,builder->builder.templates_num);
	builder->ghost_sizes=ghost_sizes;
	return builder;
}

// TODO do a sneaky cartesian product along with furtivity option (change order to have change in each consecutive template
bool sneaky_command_builder_next_command(Command_builder* builder) { // Cartesian product
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

