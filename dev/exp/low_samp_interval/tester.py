# (one guess per attack), but uses "loi des grands nombre" to narrow intervall of incertitude until two sets are totally disjoint, wich may or may not be faster than bernouilly stuff
import scipy.stats
import math
from runstats import Statistics
from clear_comp.auth import Bad_auth

class Interval_tester:

    def __init__(self, fixed, random):
        self.theorical_mean = fixed + 0.5 * random 
        self.auth = Bad_auth(None, fixed, random, None, None)
        self.stat = Statistics()

    def reset(self):
        self.cpt=0
        self.stat = Statistics()

    def generate_data(self,x):
        for i in range(x):
            self.stat.push( self.auth.simulate('bla') )

    def is_intervall_ok(self, confidence_level):
        confidence_interval = scipy.stats.t.interval(confidence_level, len(self.stat)-1, self.stat.mean(), self.stat.stddev(ddof=1)/math.sqrt(len(self.stat)))
        return confidence_interval[0] < self.theorical_mean < confidence_interval[1], confidence_interval

