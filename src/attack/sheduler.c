#include "sheduler.h"

Sheduler* new_sheduler(bool guessing){
	Sheduler* sheduler = malloc (sizeof(sheduler));
}


static Big_int sheduler_heuristic(Sheduler_unit* attacker, Shared_data* shared_data){

	return attacker_estimate(&attacker->attacker, shared_data) * attacker->considered;
}


void sheduler_remove_at(Sheduler* sheduler, Small_int pos){
	Sheduler_unit* attacks = sheduler->attackers;
	for ( Small_int j = pos+1; j < sheduler->attack_num; j++)
	{
		attacks[j] = attacks[j-1];
	}
}

static Sheduler_unit* sheduler_chose(Sheduler* sheduler, Shared_data* data){

	Sheduler_unit* min_unit = sheduler->attackers;
	size_t min = -1;
	for (Small_int i = 1; i< sheduler->attack_num; i++){
		Sheduler_unit* unit= sheduler->attackers + i;
		Big_int heuristic = sheduler_heuristic(unit, data);
		if (heuristic == 0){
			sheduler_remove_at(sheduler, i);
			i--;
			continue;
		}
		if (heuristic < min){
			min_unit = unit;
		}
	}
	return min_unit;
}

static void sheduler_unit_attack(Sheduler_unit* unit, Shared_data* data){
	//attacker_attack(unit->attacker);
	attacker_attack(NULL, data);
	unit->considered = 1;
}

void sheduler_attack(Sheduler* sheduler, Shared_data* data){
	Sheduler_unit* unit = sheduler_chose(sheduler, data);
	sheduler_unit_attack(unit, data);
	sheduler->attack_cpt++;
}


