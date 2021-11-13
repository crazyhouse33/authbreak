# (one guess per attack), but uses "loi des grands nombre" to narrow intervall of incertitude until two sets are totally disjoint, wich may or may not be faster than bernouilly stuff
from runstats import Statistics

class Flat_attacker(Attacker):

     def __init__(self, charset):
        self.history = {}

    def save_run(self, letter, time):
        current = self.history.get(letter, Statistics())
        current.push(time)
        self.history[letter] = current

    def choose_next_letter(self):
        try: 
            letter = next(self.generator)
        except:
            self.generator(generator(self.charset))
            letter = next(self.generator)
        

