from abc import ABCMeta, abstractclassmethod
from Organizm import Organizm
from random import randint

class Zwierze(Organizm):
    __metaclass__ = ABCMeta
    def __init__(self, new_x, new_y):
        pass

    def akcja(self, mapa_organizmow):
        czyKolizja = 0

        #print("uwaga wchodze miedzy dupy")
        def kolizja(mapa_organizmow, stare_x, stare_y, nowy_x, nowy_y):
            listaZwierzat = ["K", "L", "S", "O", "W"]
            listaRoslin = ["J", "T", "G"]
            
            #print("kolizja")
            if mapa_organizmow[nowy_x][nowy_y].getZnak() == mapa_organizmow[stare_x][stare_y].getZnak(): #rozmnazanie!!!!!!!!!!!!!!!!
                mapa_organizmow[stare_x][stare_y].setCzyRozmnazac(1)
                #print("lej dupa")
            #elif mapa_organizmow[
            

            elif mapa_organizmow[nowy_x][nowy_y].getZnak() == "L":
                #print(mapa_organizmow[stare_x][stare_y].getZnak())
                print(mapa_organizmow[stare_x][stare_y].getZnak(), "Nie wchodzi na lwa")
            elif mapa_organizmow[nowy_x][nowy_y].getZnak() in listaZwierzat:
                #print("kac dupa")
                if mapa_organizmow[stare_x][stare_y].getZnak() == "S":
                    if mapa_organizmow[stare_x][stare_y].getSila() < mapa_organizmow[nowy_x][nowy_y].getSila():
                        print("Lis nie wchodzi na ", mapa_organizmow[nowy_x][nowy_y].getZnak())
                        pass
                if mapa_organizmow[stare_x][stare_y].getSila() >= mapa_organizmow[nowy_x][nowy_y].getSila():
                    #print("burdel")
                    mapa_organizmow[nowy_x][nowy_y] = None
                    mapa_organizmow[nowy_x][nowy_y] = mapa_organizmow[stare_x][stare_y]
                    print(mapa_organizmow[stare_x][stare_y].getZnak(), "unicestwia", mapa_organizmow[nowy_x][nowy_y].getZnak())

                    mapa_organizmow[nowy_x][nowy_y].setPolozenie_x(nowy_x)
                    mapa_organizmow[nowy_x][nowy_y].setPolozenie_y(nowy_y)
                    
                    mapa_organizmow[stare_x][stare_y] = None
                    mapa_organizmow[stare_x][stare_y] = Organizm()
                    mapa_organizmow[nowy_x][nowy_y].setCzySmierc(1)
                else:
                    mapa_organizmow[stare_x][stare_y].setZnak(".")
                    mapa_organizmow[stare_x][stare_y].setCzySmierc(1)
                    print(mapa_organizmow[stare_x][stare_y].getZnak(), "zostanie zabity")
            elif mapa_organizmow[nowy_x][nowy_y].getZnak() in listaRoslin:
                #mapa_organizmow[stare_x][stare_y].akcja(mapa_organizmow)
                if mapa_organizmow[stare_x][stare_y].getZnak() == "K" and mapa_organizmow[nowy_x][nowy_y].getZnak() == "T":
                    temp = mapa_organizmow[stare_x][stare_y].getSila()
                    temp =+ 3
                    mapa_organizmow[stare_x][stare_y].getSet(temp)
                    print("Krowa trawe zjadla")
                if mapa_organizmow[nowy_x][nowy_y].getZnak() == "J":
                    mapa_organizmow[stare_x][stare_y].setCzySmierc(1)
                    mapa_organizmow[nowy_x][nowy_y].setCzySmierc(1)
                    print(mapa_organizmow[stare_x][stare_y].getZnak(), "ginie od jagody :(")
                    pass
                if mapa_organizmow[nowy_x][nowy_y].getZnak() == "G":
                   dodatek = mapa_organizmow[stare_x][stare_y].getSila()
                   dodatek += 3
                   mapa_organizmow[stare_x][stare_y].setSila(dodatek)
                   print(mapa_organizmow[stare_x][stare_y].getZnak(), "zjadlo guarane")

                mapa_organizmow[nowy_x][nowy_y] = None
                mapa_organizmow[nowy_x][nowy_y] = mapa_organizmow[stare_x][stare_y]

                mapa_organizmow[nowy_x][nowy_y].setPolozenie_x(nowy_x)
                mapa_organizmow[nowy_x][nowy_y].setPolozenie_y(nowy_y)
                    
                mapa_organizmow[stare_x][stare_y] = None
                mapa_organizmow[stare_x][stare_y] = Organizm()
                mapa_organizmow[nowy_x][nowy_y].setCzySmierc(1)

        x = self.getPolozenie_x()
        y = self.getPolozenie_y()
        wKierunku_x = randint(-1, 1)
        wKierunku_y = randint(-1, 1)

        temp_x = 0
        temp_y = 0
        
        while True:
            if wKierunku_x != 0 or wKierunku_y != 0:
                temp_x = wKierunku_x + x
                temp_y = wKierunku_y + y
                
                if 20 > temp_x >= 0 and 20 > temp_y >= 0:
                    break

            wKierunku_x = randint(-1, 1)
            wKierunku_y = randint(-1, 1)

        if mapa_organizmow[temp_x][temp_y] == None or mapa_organizmow[temp_x][temp_y].getZnak() == ".":
            self.setPolozenie_x(temp_x)
            self.setPolozenie_y(temp_y)
            mapa_organizmow[temp_x][temp_y].setZnak(mapa_organizmow[x][y].getZnak()) #= mapa_organizmow[x][y]
            mapa_organizmow[x][y] = None
            mapa_organizmow[x][y] = Organizm()
            mapa_organizmow[x][y].setCzySmierc(1)
            #mapa_organizmow[x][y]
        else:
            #print("NIE KURWA NIE WCHODZE I CHUJ")
            kolizja(mapa_organizmow, x, y, temp_x, temp_y)


            