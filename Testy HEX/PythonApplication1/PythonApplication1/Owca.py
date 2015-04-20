from Zwierze import Zwierze

class Owca(Zwierze):
    def __init__(self, new_x, new_y):
        self.setZnak("O")
        self.setSila(4)
        self.setInicjatywa(4)
        self.setPolozenie_x(new_x)
        self.setPolozenie_y(new_y)
        self.setCzyRozmnazac(0)
        self.czySmierc = 0


