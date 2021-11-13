
random.seed(10)

class Bad_auth:
    
    # Diff factor = ratio regular_time/favorised
    def __init__(self, advantaged_letter, regular_time, random_power, diff_factor):
        self.letter = advantaged_letter
        self.regular_time = regular_time
        self.random_power = random_power
        self.diff_factor = diff_factor

    def simulate(self,letter):
        time = self.regular_time
        if letter == self.advantaged_letter:
            time += (self.diff_factor * time)
        random_delta = random_power * random.random()

        return time + random_delta

    # Reset seed so each attack get the same random serie
    def reset_seed():
        random.seed(10)






