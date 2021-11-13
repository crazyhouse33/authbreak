#include "sheduler.h"

Sheduler* new_sheduler(bool guessing){
	Sheduler* sheduler = malloc (sizeof(sheduler));
}


static Big_int sheduler_heuristic(Sheduler_unit* attacker, Shared_data* shared_data){

	return attacker_estimate(&attacker->attacker, shared_data) * attacker->considered;
}


void sheduler_remove_at(Sheduler* sheduler, Small_int pos){
	Sheduler_unit* attacks = sheduler->attackers;
	Sheduler_unit removed_attack = attacks[pos];
	for ( Small_int j = pos+1; j < sheduler->attack_num; j++)
	{
		attacks[j] = attacks[j-1];
	}
	unregister( sheduler->data, removed_attack.attacker.consumer_of);
}

static Sheduler_unit* sheduler_chose(Sheduler* sheduler){

	Sheduler_unit* min_unit = sheduler->attackers;
	size_t min = -1;
	for (Small_int i = 1; i< sheduler->attack_num; i++){
		Sheduler_unit* unit= sheduler->attackers + i;
		Big_int heuristic = sheduler_heuristic(unit, sheduler->data);
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

static void sheduler_unit_attack(Sheduler_unit* unit, Shared_data* data, Try* try){
	attacker_attack(&unit->attacker, data, try);
	unit->considered = 1;
}

void sheduler_attack(Sheduler* sheduler, Try* try){
	Shared_data* data = sheduler->data;
	Sheduler_unit* unit = sheduler_chose(sheduler);
	sheduler_unit_attack(unit, data, try);
	sheduler->attack_cpt++;
}


