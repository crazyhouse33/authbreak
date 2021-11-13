# (one guess per attack), but uses "loi des grands nombre" to narrow intervall of incertitude until two sets are totally disjoint, wich may or may not be faster than bernouilly stuff
import scipy.stats
import math
from attackers.flat import Flat_attacker
from runstats import Statistics
import logging
import runstats

class Equilibred_flat(Flat_attacker):
    def __init__(self, charset, confidence_level):
        super().__init__(charset, confidence_level)
        self.min_other_serie = 0
        self.best_letter = charset[0]
        self.other_series = Statistics()

    def reset(self):
        super().reset()
        self.history = {letter: Statistics() for letter in self.charset}

    def _separate_series(self, best_letter):
        other_series = Statistics()
        min_serie= None
        min_serie_len = float('inf')

        for i, serie in self.history.items():
            if i != best_letter:
                other_series += serie
                if len(serie)<min_serie_len:
                    min_serie_len=len(serie)
                    min_serie=i
        # caching infos for next letter selection
        self.min_other_serie =min_serie
        self.best_letter = best_letter
        self.other_series = other_series
        return other_series

    def choose_next_letter(self):
        best_serie = self.history.get(self.best_letter, Statistics())

        if (len(best_serie) <= len(self.other_series)):
            return self.best_letter
        else:
            return self.min_other_serie
