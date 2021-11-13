#include "brutforcer.h"
size_t brutforcer_estimate( Attacker* brutforcer, Shared_data* shared_data){
        Brutforcer_data* data= brutforcer->data;
        return data->size - data->cpt;
}

void brutforcer_attack(Attacker* brutforcer, Shared_data* shared_data, Try* try){
        Brutforcer_data* data= (Brutforcer_data*) brutforcer->data;
        data->cpt++;
        sneaky_command_builder_next_command(data->builder);
        try->argv= data->builder->builder.argv;
        try->prompts = data->builder->builder.prompts;
        return;
}

Attacker* brutforcer_new(Command_builder* builder){
        Attacker* brutforcer = malloc(sizeof(Attacker*));
        Brutforcer_data* data = malloc(sizeof(Brutforcer_data));
        brutforcer->data = data;
        data->builder = command_builder_sneakify(builder);
        data->size = command_builder_size(&data->builder->builder);
        data->cpt  = 0;
        brutforcer->consumer_of = NULL;
        return brutforcer;
}

