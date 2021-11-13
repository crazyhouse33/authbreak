#include "enum.h"
#include "shared_data.h"
#include "try.h"
#define NEVER = 0
#define ATTACKS(XX) \
    XX(brutforcer,"brutforcer",) \

DECLARE_ENUM(Attack_enum,ATTACKS);

#define ATTACK_TYPES(XX) \
    XX(vertical,"vertical",) \
    XX(horizontal,"horizontal",) \

DECLARE_ENUM(Attack_type, ATTACK_TYPES);

//This time we go function pointer (Wish I never eared it was less efficient)
typedef struct Attacker{ // here it should be attacker and no void*
		void (*attack_ptr)(void* attacker, Shared_data* data, Try* try);
		size_t (*estimate_ptr)(void* attacker, Shared_data* data);
		Data_structure* consumer_of; // usefull to know to which point we still need to compute shared data
		void* data;
		Attack_type type;
}Attacker;

void attacker_attack(Attacker* attacker, Shared_data* data, Try* try);
// Set try to the next attack try

size_t attacker_estimate(Attacker* attacker, Shared_data* data);
// return estimate amount of attack until finding working creds
