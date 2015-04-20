from Zwierze import Zwierze

class Lis(Zwierze):
    def __init__(self, new_x, new_y):
        self.setZnak("S")
        self.setSila(3)
        self.setInicjatywa(7)
        self.setPolozenie_x(new_x)
        self.setPolozenie_y(new_y)
        self.setCzyRozmnazac(0)
        self.czySmierc = 0


