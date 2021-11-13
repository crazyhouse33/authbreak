import panda
from abc import ABC, abstractmethod

class Attacker(ABC):
    
    def __init__(self, charset):
        self.charset = charset 

    def run(self, auth_system):
        while not self.done():
            self.attack(auth_system)

    def attack(auth_system, letter)
        letter = self.choose_next_letter()
        time = auth_system.simulate(letter)
        self.save_run(letter, time)
        return self.done()

    @abstractmethod
    def save_run(self, letter, time):
        return 

    
    @abstractmethod
    def done(self):
        """Return true if it's time to give up"""
        return 

    @abstractmethod
    def choose_next_letter(self):
        """Chose next letter to try"""
        return 

        
