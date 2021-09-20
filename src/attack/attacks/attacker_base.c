#include "attacker_base.h"

DEFINE_ENUM(Attack_type, "\"%s\" is not a supported attack, chose amongs this options: \n%s\n", "\"%s\" is ambigious for an attack, choose among: \n%s\n", ATTACK_TYPES);

Attack_return* attacker_attack(Attacker* attacker, Shared_data* data){
	return (*(attacker->estimate_ptr))(attacker, data);
}

size_t attacker_estimate(Attacker* attacker, Shared_data* data){
	return (*(attacker->attack_ptr))(attacker, data);
}
