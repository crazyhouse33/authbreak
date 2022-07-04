# (one guess per attack), but uses "loi des grands nombre" to narrow in
import scipy.stats
import math
from attackers.one_letter.attacker import Attacker
from runstats import Statistics
import logging
import runstats
import numpy.polynomial.polynomial as poly
import warnings

class Flat_attacker(Attacker):

    def __init__(self, charset, confidence_level):
        super().__init__(charset,confidence_level)

    def reset_data(self):
        self.cpt=0
        self.history = {}

    # We save individual run_stats for each letter
    def save_run(self, letter, time):
        current = self.history.get(letter, Statistics())
        current.push(time)
        self.history[letter] = current

    def choose_next_letter(self):
        next_item = self.charset[self.cpt % len(self.charset) ]
        self.cpt += 1 
        return next_item

    # To get a asked error rate, we need to correct the confidence_level, otherwise this algo is too strict
    # This function result from establishing the tree error rate of the decision considering the direction of the error(left or right from interval)  and computing the inverse function
    def set_confidence_level(self, confidence_level):
        # The mean is in the interval with proba X => error rate =  0.5x + 0.5 x**2
        # Thus we just resolve the equation to obtain wanted error rate
        if confidence_level < 0.5:
            warnings.warn(f"Given confidence_level is too low to equilibrate error rate: {confidence_level}")
            self.intervalle_proba = confidence_level
        self.intervalle_proba = poly.polyroots([0.5 - confidence_level, 0, 0.5])[1]

    def score_letter(self):
        pass

    #TODO Check if we can find some stuff about singinfiance of difference of means online. This would probably allow to return anytime a good indication of "isWorking" value

    # We are done when intervall of trust are disjoint
    def done(self):
        best_letter, best_serie = max(self.history.items(), key = lambda x: x[1].mean())
        other_series = self._separate_series(best_letter)
        if len(best_serie) < 30 or len(other_series) < 30:
            return False, best_letter
        confidence_interval_best = scipy.stats.t.interval(self.intervalle_proba, len(best_serie)-1, best_serie.mean(), (best_serie.stddev(ddof=1) or 0.0000000000000000001) / math.sqrt(len(best_serie)))
        confidence_interval_other = scipy.stats.t.interval(self.intervalle_proba, len(other_series)-1, other_series.mean(), (other_series.stddev(ddof=1) or 0.0000000000000000001)/math.sqrt(len(other_series)))

  #      print(f'{self.cpt}: {confidence_interval_best} {confidence_interval_other}')
        #print({letter: (len(v),v.mean(),v.stddev()) for letter, v in self.history.items()})
        
        return confidence_interval_best[0] > confidence_interval_other[1], best_letter

    def _separate_series(self,letter):
        other_series = Statistics()
        for i, serie in self.history.items():
            if i != letter:
                other_series += serie
        return other_series

    def __str__(self):
        return "Flat statistic attacker"







