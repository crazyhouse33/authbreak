#include "attacker_base.h"

DEFINE_ENUM(Attack_type, "\"%s\" is not a supported attack, chose amongs this options: \n%s\n", "\"%s\" is ambigious for an attack, choose among: \n%s\n", ATTACK_TYPES);

void attacker_attack(Attacker* attacker, Shared_data* data, Try* try){
	void (*attack_ptr)(void* attacker, Shared_data* data, Try* try);
	attack_ptr = attacker->attack_ptr;
	return attack_ptr(attacker, data, try);
}

size_t attacker_estimate(Attacker* attacker, Shared_data* data){
	size_t (*estimate_ptr)(void* attacker, Shared_data* data);
	estimate_ptr = attacker->estimate_ptr;
	return estimate_ptr(attacker, data);
}
