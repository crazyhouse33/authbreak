import random
random.seed(10)

class Bad_auth:
    
    # Diff factor = ratio regular_time/favorised
    def __init__(self, password, regular_time, random_power, name):
        self.password = password + '0' # Simulating null char
        self.regular_time = regular_time
        self.random_power = random_power
        self.name = name

    def simulate_auth(self, word):
        total_time = 0
        word += '0'
        for pos, letter in enumerate(word):
            time, sucess = self.simulate_letter(letter, self.password[pos])
            total_time += time
            if not sucess: 
                break
        random_delta = self.random_power * random.random()
        return total_time + random_delta


    def simulate_letter(self, letter, good_letter):
        time = self.regular_time
        return time, letter == good_letter

    def __str__(self):
        return f"{self.name}"

    # Reset seed so each attack get the same random serie
    def reset_seed(seed):
        random.seed(seed)






