from abc import ABC, abstractmethod
import logging

class Attacker(ABC):

    def __init__(self, charset):
        self.charset = charset 

    def run(self, auth_system):
        cpt = 0
        done = False
        while not done:
            done, best_letter = self.attack(auth_system)
            cpt +=1
        return best_letter, cpt

    def attack(self, auth_system):
        letter = self.choose_next_letter()
        time = auth_system.simulate(letter)
        logging.debug(f'{letter} {time}')
        self.save_run(letter, time)
        return self.done()

    def choose_next_letter(self):
        return max(self.charset, self.score_letter)

    @abstractmethod
    def save_run(self, letter, time):
        return 


    @abstractmethod
    def done(self):
        """Return true if it's time to give up, among with the best letter yet"""
        return 

    @abstractmethod
    def score_letter(self):
        """Euristic to order tries"""
        return 


