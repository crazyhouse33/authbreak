#include "try.h"
#include "attacker_base.h"
#include <sys/types.h>
#include <commandbuild_sneaky.h>

typedef struct Brutforcer_data{ 
	size_t cpt;
	size_t size; 
	Sneaky_command_builder* builder;
}Brutforcer_data;


size_t brutforcer_estimate( Attacker* brutforcer, Shared_data* data);

void brutforcer_attack(Attacker* brutforcer, Shared_data* data, Try* try);

// TODO make a injection point class unstead of using a builder
Attacker* brutforcer_new(Command_builder* builder);
