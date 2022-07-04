from abc import ABC, abstractmethod

class Word_attacker(ABC):

    def __init__(self, charset, confidence_intervalle, attacker_class, secondary_confidence = 0.8):
        self.attacker = attacker_class(charset, secondary_confidence)
        self.confidence_intervalle = confidence_intervalle
        self.reset_data()

    def reset_data(self):
        self.accumulator = ""

    def attack(self, auth_system):
        # Each time attacker think he is done, we double check it at last letter
        next_letter = ""
        while next_letter is not None:
            self.accumulator += next_letter
            next_letter, _ = self.attacker.run(auth_system, prefix = self.accumulator)

        if not self.retry_last_iteration(auth_system):
            return self.attack(auth_system)
        
        res = self.accumulator
        self.reset_data()
        return res 

    # Retry last iteration and return True if result were similar
    def retry_last_iteration(self):
        last_it_accumulator = self.accumulator[::-1]
        self.attacker.set_confidence_level(self.confidence_intervalle)
        letter, _ = self.attacker.run(prefix = self.accumulator[::-1])
        if letter != last_it_accumulator[-1]:
            self.accumulator = last_it_accumulator + letter
            self.attacker.set_confidence_level(self.secondary_confidence)
            return False
        else:
            return True

