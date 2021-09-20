#include "enum.h"
#include "shared_data.h"
#define NEVER = 0
#define ATTACKS(XX) \
    XX(brutforcer,"brutforcer",) \

DECLARE_ENUM(Attack,ATTACKS);

#define ATTACK_TYPES(XX) \
    XX(vertical,"vertical",) \
    XX(horizontal,"horizontal",) \

DECLARE_ENUM(Attack_type, ATTACK_TYPES);

typedef struct Attack_return{
		char** argv;
		char** prompts;
}Attack_return;

//This time we try function pointer (sick of this C bullshit)
typedef struct Attacker{ // here it should be attacker and no void*
		Attack_return* (*attack_ptr)(void* attacker, Shared_data* data);
		size_t (*estimate_ptr)(void* attacker, Shared_data* data);
		unsigned short* consumer_of; // usefull to know to which point we still need to compute shared data
		void* data;
		Attack_type type;
}Attacker;

Attack_return* attacker_attack(Attacker* attacker, Shared_data* data);
// return next try 

size_t attacker_estimate(Attacker* attacker, Shared_data* data);
// return estimate amount of attack until finding working creds
