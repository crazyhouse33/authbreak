import random
random.seed(10)

class Bad_auth:
    
    # Diff factor = ratio regular_time/favorised
    def __init__(self, advantaged_letter, regular_time, random_power, diff_factor, name):
        self.advantaged_letter = advantaged_letter
        self.regular_time = regular_time
        self.random_power = random_power
        self.diff_factor = diff_factor
        self.name = name

    def simulate(self, letter):
        time = self.regular_time
        if letter == self.advantaged_letter:
            time *= self.diff_factor 
        random_delta = self.random_power * random.random()

        return time + random_delta

    def __str__(self):
        return f"{self.name}"

    # Reset seed so each attack get the same random serie
    def reset_seed(seed):
        random.seed(seed)






