from abc import ABCMeta, abstractclassmethod
from Organizm import Organizm
from random import randint

class Roslina(Organizm):
    __metaclass__ = ABCMeta
    def __init__(self, new_x, new_y):
        pass
    def akcja(self, mapa_organizmow):
        losowa = randint(0, 10)
        if losowa == 1:
            self.setCzyRozmnazac(1)
        #mapa_organizmow[stare_x][stare_y].setCzyRozmnazac(1)


