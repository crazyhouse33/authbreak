#!/usr/bin/python3

import sys
from auth import Bad_auth
from attackers.one_letter.flat import Flat_attacker
from attackers.one_letter.flatv2 import Flat_attacker_v2
from attackers.one_letter.flatv3 import Flat_attacker_v3
from attackers.one_letter.equilibred_flat import Equilibred_flat

import argparse
import logging
import parser

good_letter = 'e'

auths = [
        #Bad_auth(good_letter, 1, 0,  'no network' ), 
        #Bad_auth(good_letter, 1, 1,  'amazing network'),
        Bad_auth(good_letter, 1, 7, 'ok network'), 
        #Bad_auth(good_letter, 1, 10,  'bad network'), 
        #Bad_auth(good_letter, 1, 100, 'terrible network'),
        ]

charset = 'abcdefghi'
confiance = parser.options.confiance
seeds=range(1000)

attackers = [
        #Equilibred_flat(charset, confiance), # 10000 ok network:0.15%, 382.393
        #with equilibrated: ok network:0.15%, 382.3855

        #Flat_attacker(charset, confiance), #100 seeds ok network:1.0%, 724.42
        #Flat_attacker_v3(charset, confiance),
        Flat_attacker_v2(charset, confiance)
        ]

def evaluate_attack(attacker, auths, seeds):
    print (attacker, ":\n", file = sys.stderr)
    for auth in auths:
        errors=0
        total_tries = 0
        for cpt, seed in enumerate(seeds, start=1):
            Bad_auth.reset_seed(seed)
            sucess, tries = attack_auth(attacker,auth)
            if not sucess:
                errors+=1
            total_tries +=tries
            print(f'{seed}:{(cpt-errors)/cpt}, {total_tries/cpt} {attacker.intervalle_proba}' )

def attack_auth(attacker, auth):
    letter, cpt = attacker.run(auth)
    return letter == good_letter, cpt

for attacker in attackers:
    evaluate_attack(attacker, auths, seeds)



