from abc import ABC, abstractmethod
import logging

class Attacker(ABC):

    def __init__(self, charset, confidence_level):
        self.charset = charset 
        self.set_confidence_level(confidence_level)
        self.reset_data() 

    def run(self, auth_system, prefix = ""):
        cpt = 0
        done = False
        while not done:
            done, best_letter = self.attack(auth_system, prefix=prefix)
            cpt +=1
        self.reset_data() 
        return best_letter, cpt

    def attack(self, auth_system, prefix = ""):
        letter = self.choose_next_letter()
        time = auth_system.simulate_auth(prefix + letter)
        logging.debug(f'{letter} {time}')
        self.save_run(letter, time)
        return self.done()

    def set_confidence_level(self, confidence_level):
        self.confidence_level = confidence_level

    def choose_next_letter(self):
        return max(self.charset, self.score_letter)

    @abstractmethod
    def save_run(self, letter, time):
        return 

    @abstractmethod
    def done(self):
        """Return true if it's time to terminate, among with the best letter yet"""
        return 

    @abstractmethod
    def score_letter(self):
        """Euristic to order tries"""
        return 


