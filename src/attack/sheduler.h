#define Small_int unsigned short
#define Big_int unsigned long
#include "attacker_base.h"
#include "try.h"
#include "shared_data.h"

typedef struct Sheduler_unit{
                Attacker attacker;
		int considered;//considered number of time since last time attack executed
} Sheduler_unit;

typedef struct Sheduler{
		Shared_data* data; // Shared data among all attacks from sheduler
                Sheduler_unit* attackers;
		Small_int attack_num; 
		Big_int attack_cpt;//number of attack ran
} Sheduler;

//Chose next attack and let it set the next Try
void sheduler_attack(Sheduler* sheduler,  Try* try);

//Create a sheduler with given attacks
Sheduler* sheduler_new(Sheduler* sheduler, Attacker* attacks);

//Remove attacker at given position
void sheduler_remove(Small_int pos);


