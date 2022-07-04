#!/usr/bin/python3

import sys
from auth import Bad_auth
from attackers.one_letter.flatv2 import Flat_attacker_v2
from attackers.one_letter.flatv3 import Flat_attacker_v3
from attackers.one_letter.equilibred_flat import Equilibred_flat
from attackers.word_attacker import Word_attacker 

import argparse
import logging
import parser

good_word = 'eee'

auths = [
        #Bad_auth(good_letter, 1, 0, 2, 'no network' ), 
        #Bad_auth(good_letter, 1, 1, 2, 'amazing network'),
        Bad_auth(good_word, 1, 7, 2, 'ok network'), 
        #Bad_auth(good_letter, 1, 10, 2, 'bad network'), 
        #Bad_auth(good_letter, 1, 100, 2, 'terrible network'),
        ]

charset = 'abcdefghi'
confiance = parser.options.confiance
seeds=range(1000)
attackers = [
        Word_attacker(charset, confiance, Equilibred_flat)
        ]

def evaluate_attack(attacker, auths, seeds):
    print (attacker, ":\n", file = sys.stderr)
    for auth in auths:
        errors=0
        for cpt, seed in enumerate(seeds, start=1):
            Bad_auth.reset_seed(seed)
            sucess = attack_auth(attacker,auth)
            if not sucess:
                errors+=1
            print(f'{seed}:{(cpt-errors)/cpt}' )

def attack_auth(attacker, auth):
    word = attacker.attack(auth)
    return word == good_letter

for attacker in attackers:
    evaluate_attack(attacker, auths, seeds)



