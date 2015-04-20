from Zwierze import Zwierze

class Lew(Zwierze):
    def __init__(self, new_x, new_y):
        self.setZnak("L")
        self.setSila(11)
        self.setInicjatywa(7)
        self.setPolozenie_x(new_x)
        self.setPolozenie_y(new_y)
        self.setCzyRozmnazac(0)
        self.czySmierc = 0


