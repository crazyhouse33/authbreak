brutforcer_estimate( Attacker brutforcer, sharedData* data){
	Brutforcer_data* data= brutforcer->data;
	return data->size - data->cpt;
}

brutforcer_attack(char ***argv, char***prompt, Attacker* brutforcer){
	Brutforcer_data* data= brutforcer->data;
	data->cpt++;
	sneaky_command_builder_next_command(data->builder);
	argv* = data->builder.argv;
	prompt* = data->builder->builder.prompt;
}

Attacker* brutforcer_new(Command_builder* builder){
	Attacker* brutforcer = malloc(sizeof(Attacker*));
	Brutforcer_data* data = malloc(sizeof(Brutforcer_data));
	brutforcer->data = data; 
	data->builder = command_builder_sneakify(builder);
	data->size = command_builder_get_size(data->builder);
	data->cpt  = 0;
	brutforcer->consumer_of = NULL;
	return 
}
