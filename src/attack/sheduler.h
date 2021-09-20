#define Small_int unsigned short
#define Big_int unsigned long
#include "attacker_base.h"

typedef struct Sheduler_unit{
                Attacker attacker;
		int considered;//considered number of time since last time attack executed
} Sheduler_unit;

typedef struct Sheduler{
                Sheduler_unit* attackers;
		Small_int attack_num; 
		Big_int attack_cpt;//number of attack ran
} Sheduler;

//Chose next attack and run it
void sheduler_attack(Sheduler* sheduler, Shared_data* data);

//Create a sheduler with given attacks
Sheduler* sheduler_new(Sheduler* sheduler, Attack* attacks);

//Remove attacker at given position
void sheduler_remove(Small_int pos);


