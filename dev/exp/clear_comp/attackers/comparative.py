# This one try to favorise the winner. It does so by simulating fights between couples, and favorise the letter that win for futur runs. Each exp take 2 guess, but there is early stopage, and the theoric distribution of wins is Binomial(n,0.5), which may accelerate things compare to the other uknown distribution approach

class Comparative_attacker(Attacker):

    def __init__(self):
        super.__init__(self)
        self.generator = generator(self.charset)


    def choose_next_letter(self):
        try: 
            letter = next(self.generator)
        except:
            self.generator(generator(self.charset))
            letter = next(self.generator)
        

