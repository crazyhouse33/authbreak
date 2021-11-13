# (one guess per attack), but uses "loi des grands nombre" to narrow intervall of incertitude until two sets are totally disjoint, wich may or may not be faster than bernouilly stuff
import scipy.stats
import math
from attackers.equilibred_flat import Equilibred_flat
from runstats import Statistics
import logging
import runstats

# This one comput the theorical difference distribution with the one that you obtained 

class Flat_attacker_v3(Equilibred_flat):

    def done(self):
        best_letter, best_serie = max(self.history.items(), key = lambda x: x[1].mean())
        other_series = self._separate_series(best_letter)
        if len(best_serie) < 5 or len(other_series) < 5:
            return False, best_letter
        stddev = (best_serie + other_series).stddev(ddof=1)
        #size = min(len(best_serie), len(other_series)) # 1000 ok network:0.0%, 1646.289
        #size = len(best_serie)+ len(other_series) # 100 ok network:26.0%, 132.01 # equi 1000 ok network:7.8%, 199.58


        
        #the_min = min(len(best_serie), len(other_series)) # 
        #size = int(the_min + 0.5 *  (len(best_serie) - the_min + len(other_series) - the_min)) 1000 ok network:3.1%, 338.712

        size = int((len(best_serie) + len(other_series))/2) #1000ok network:3.1%, 338.712 equi 1000 ok network:1.5%, 388.344
        confidence_interval = scipy.stats.t.interval(self.confidence_level, size, best_serie.mean() - other_series.mean(), (2*stddev / math.sqrt(size))or 0.0000000000000000001) # Var[X-Y] = var x + var y
        #https://en.wikipedia.org/wiki/Student%27s_t-test#Independent_two-sample_t-test
#        import pdb;pdb.set_trace()
        if confidence_interval[0] >0:
            pass
            #logging.info({letter: (len(v),v.mean(),v.stddev()) for letter, v in self.history.items()})
        return confidence_interval[0] >0, best_letter

    def __str__(self):
        return "Flat statistic attacker V2"







