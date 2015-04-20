from Roslina import Roslina
from random import randint

class Trawa(Roslina):
    """description of class"""
    def __init__(self, new_x, new_y):
        self.setZnak("T")
        self.setPolozenie_x(new_x)
        self.setPolozenie_y(new_y)
        self.setInicjatywa(0)
        self.setSila(0)
    def akcja(self, mapa_organizmow):
        losowa = randint(0, 10)
        if losowa == 1:
            self.setCzyRozmnazac(1)

