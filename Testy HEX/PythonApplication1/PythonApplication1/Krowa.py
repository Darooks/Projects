from Zwierze import Zwierze

class Krowa(Zwierze):
    def __init__(self, new_x, new_y):
        self.setZnak("K")
        self.setSila(2)
        self.setInicjatywa(5)
        self.setPolozenie_x(new_x)
        self.setPolozenie_y(new_y)
        self.setCzyRozmnazac(0)
        self.czySmierc = 0


