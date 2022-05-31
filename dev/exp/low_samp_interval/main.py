#!/usr/bin/python3
import sys
sys.path.append("..") # Adds higher directory to python modules path.
from clear_comp.auth import Bad_auth
from tester import Interval_tester

good_letter = 'e'

sample_size = 5
confidence = 0.25
seeds = range(1000)

testers = [
        #Interval_tester(1,2), 
        #Interval_tester(1,7), 
        Interval_tester(1,100), 
        ]

for tester in testers:
    errors=0
    total_tries = 0
    print("tester", tester)
    for cpt, seed in enumerate(seeds, start=1):
        tester.reset()
        tester.generate_data(sample_size)
        sucess, interval = tester.is_intervall_ok(confidence)
        if not sucess:
            errors+=1
        total_tries +=1
        print(f'{seed}:{(cpt-errors)/cpt} {tester.theorical_mean}, {interval}' )
