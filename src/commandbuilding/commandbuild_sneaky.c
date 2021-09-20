#include "pgcd.h" 
#include "commandbuild_sneaky.h"

static unsigned int* sneaky_command_builder_get_templates_sizes(){

}

static void __init_sneaky_part( Sneaky_command_builder* builder) {
	size_t* ghost_sizes = malloc(sizeof(size_t) * builder->builder.templates_num);
	size_t* sizes = malloc(sizeof(size_t) * builder->builder.templates_num);
	builder->pos = malloc(sizeof(size_t) * builder->builder.templates_num);

	for (int i=0; i<builder->builder.templates_num; i++){
		size_t size_i = template_size(builder->builder.templates[i]);
		ghost_sizes[i]=size_i;
		sizes[i]=size_i;
	}
	builder->sizes= sizes;
	make_prime_together(ghost_sizes,builder->builder.templates_num);
	builder->ghost_sizes=ghost_sizes;
}

Sneaky_command_builder* sneaky_command_builder_new( char *command, char **prompts) {
	Sneaky_command_builder* builder = malloc(sizeof(Sneaky_command_builder));
	command_builder_init(&builder->builder, command, prompts);
	__init_sneaky_part(builder);
	return builder;
}

Sneaky_command_builder* command_builder_sneakify( Command_builder* builder) {
	Sneaky_command_builder* new_builder = malloc(sizeof(Sneaky_command_builder));
	new_builder->builder = *builder;
	__init_sneaky_part(new_builder);
	return new_builder;
}

static bool __sneaky_command_builder_next_command_fix_rec(Sneaky_command_builder* builder, int from, size_t to_inc){
//Accumulating proper incrementation needed
	int it =from;
	while (it < builder->builder.templates_num){
		Template* template= builder->builder.templates[it];
		size_t size = builder->sizes[it];
		size_t ghost = builder->ghost_sizes[it];
		size_t theorical = builder->pos[it] + to_inc;
		size_t where = theorical % ghost;
		if (where >= size ){
			to_inc += ghost - where; 
			return __sneaky_command_builder_next_command_fix_rec(builder, 0, to_inc);
		}
		it++;
	}
	bool done=true;
	for (it = 0; it<from;it++){
		Template* template= builder->builder.templates[it];
		done &= (template->next_it == 0);
	}
	//reseting every thing to the first iteration satisfying everyone
	for (; from < builder->builder.templates_num;from++)
	{
		Template* template= builder->builder.templates[from];
		size_t ghost = builder->ghost_sizes[from];
		size_t theorical = (builder->pos[from]+to_inc)%ghost;
		done &= (theorical == 0);
		template_reset_to(template, theorical);
		template_next(template);
	}
	return done;
}

static bool __sneaky_command_builder_next_command_fix(Sneaky_command_builder* builder, int just_wrapped){
	for (int i=0; i<builder->builder.templates_num; i++){
		if ( i< just_wrapped)
			builder->pos[i] = builder->builder.templates[i]->next_it - 1;	
		else if ( i== just_wrapped)
			builder->pos[i] = builder->sizes[i];

		else
			builder->pos[i] =builder->builder.templates[i]->next_it; //Those had been early stopped by fix call
	}
	return __sneaky_command_builder_next_command_fix_rec(builder, just_wrapped, 0);
}


//The goal of this implementation is to work fast when no fix is needed
bool sneaky_command_builder_next_command(Sneaky_command_builder* builder) { 
	for (int i=0; i<builder->builder.templates_num; i++){
		char* next = template_next(builder->builder.templates[i]);
		if (next==NULL){//We reach a ghost iteration, exiting from ghost state
			return __sneaky_command_builder_next_command_fix(builder, i);
		}
	}
	return false;
}

char *sneaky_command_builder_current_command(Sneaky_command_builder* builder) {
	return command_builder_current_command(&builder->builder);
}




