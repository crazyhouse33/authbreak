# (one guess per attack), but uses "loi des grands nombre" to narrow intervall of incertitude until two sets are totally disjoint, wich may or may not be faster than bernouilly stuff
import scipy.stats
import math
from attackers.flat import Flat_attacker
from runstats import Statistics
import logging
import runstats

# This approach converge faster but pvalue aint error rate as adversited apparently
# To see if we can calculate error rate from pvalue in this particular case

class Flat_attacker_v2(Flat_attacker):

    def done(self):
        best_letter, best_serie = max(self.history.items(), key = lambda x: x[1].mean())
        other_series = self._separate_series(best_letter)
        if len(best_serie) < 5 or len(other_series) < 5:
            return False, best_letter
        stddev = (best_serie + other_series).stddev(ddof=1)
        chance = scipy.stats.ttest_ind_from_stats(best_serie.mean(), best_serie.stddev(ddof=1), len(best_serie), other_series.mean(), other_series.stddev(ddof=1), len(other_series), equal_var=True)
        #https://en.wikipedia.org/wiki/Student%27s_t-test#Independent_two-sample_t-test
#        import pdb;pdb.set_trace()
        if 1-(chance.pvalue/2) > self.confidence_level:
            logging.info({letter: (len(v),v.mean(),v.stddev()) for letter, v in self.history.items()})
        return 1-(chance.pvalue/2) > self.confidence_level, best_letter

    def __str__(self):
        return "Flat statistic attacker V2"







