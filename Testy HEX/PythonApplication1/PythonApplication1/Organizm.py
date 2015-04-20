from abc import ABCMeta, abstractclassmethod


class Organizm(object):
    __metaclass__ = ABCMeta
    znak = "."
    sila = None
    inicjatywa = None
    wiek = None
    polozenie_x = None
    polozenie_y = None
    czyRozmnazac = None
    czySmierc = 0

    def __init__(self):
        self.znak = "."
        self.sila = 0
        self.inicjatywa = 0
        self.wiek = 0
        self.polozenie_x = 0
        self.polozenie_y = 0
        self.czyRozmnazac = 0
        self.czySmierc = 0

    #####SET#####
    #@abstractmethod
    def setZnak(self, znak):
        self.znak = znak
    
    def setCzySmierc(self, wartosc):
        self.czySmierc = wartosc

    def setPolozenie_x(self, wartosc):
        self.polozenie_x = wartosc

    def setPolozenie_y(self, wartosc):
        self.polozenie_y = wartosc

    def setSila(self, wartosc):
        self.sila = wartosc

    def setCzyRozmnazac(self, wartosc):
        self.czyRozmnazac = wartosc
    
    def setInicjatywa(self, wartosc):
        self.inicjatywa = wartosc

    #####GET#####
    #@abstractmethod
    def getZnak(self):
        return self.znak

    def getCzySmierc(self):
        return self.czySmierc

    def getPolozenie_x(self):
        return self.polozenie_x

    def getPolozenie_y(self):
       return  self.polozenie_y

    def getSila(self):
        return self.sila

    def getCzyRozmnazac(self):
        return self.czyRozmnazac
    
    def getInicjatywa(self):
       return self.inicjatywa
    #@abstractmethod
    #def akcja(Organizm mapa[][])
     



