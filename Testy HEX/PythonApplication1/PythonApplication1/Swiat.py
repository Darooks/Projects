from tkinter import *
from Organizm import Organizm
from Wilk import Wilk
from Owca import Owca
from Zwierze import Zwierze
from Lew import Lew
from Lis import Lis
from Krowa import Krowa
from Trawa import Trawa
from Guarana import Guarana
from Jagoda import Jagoda
import functools
from random import randint
import pickle
import copy
import sys

class Swiat(object):
    def __init__(self):
        pass

    mapa_organizmow = [[Organizm() for i in range(20)] for j in range(20)]
    pola_mapy = [[0 for x in range(20)] for x in range(20)]
    organizmy = []

    def dodajZwierze(zwierze, organizmy, mapa_organizmow):
        x = zwierze.getPolozenie_x()
        y = zwierze.getPolozenie_y()

        organizmy.append(zwierze)
        mapa_organizmow[x][y] = zwierze

    def rysujSwiat(mapa_organizmow, pola_mapy):
        for x in range(20):
            for y in range(20):
                    if mapa_organizmow[x][y] == None or self.mapa_organizmow[x][y].getZnak() == ".":
                        self.pola_mapy[x][y]["text"] = "    " 
                    else:
                        self.pola_mapy[x][y]["text"] =  mapa_organizmow[x][y].getZnak()

        self.root.mainloop()

    def akcja(organizmy, mapa_organizmow, pola_mapy, root):
        def dodajDziecko(zwierze, organizmy, mapa_organizmow, x, y):
            organizmy.append(zwierze)
            mapa_organizmow[x][y] = zwierze

            organizmy.append(zwierze)
            mapa_organizmow[x][y] = zwierze
        ilosc = len(organizmy)
        for x in range(len(organizmy)):

            #print(len(organizmy))
            if organizmy[x] == None or organizmy[x].getCzySmierc == 1:
                print("cokolwiek")
                temp_x = getPolozenie_x()
                temp_y = getPolozenie_y()
                mapa_organizmow[temp_x][temp_y] = None
                mapa_organizmow[temp_x][temp_y] = Organizm()
                #organizmy.pop(organizmy.x())
                del organizmy[x]
            if organizmy[x] != None:
                organizmy.sort(key=lambda organizmy:organizmy.inicjatywa)
                organizmy[x].akcja(mapa_organizmow)
            #print("---->", organizmy[x].getZnak())
            if organizmy[x] == None or organizmy[x].getCzySmierc == 1:
                print("cokolwiek")
                temp_x = getPolozenie_x()
                temp_y = getPolozenie_y()
                mapa_organizmow[temp_x][temp_y] = None
                mapa_organizmow[temp_x][temp_y] = Organizm()
                #organizmy.pop(organizmy.x())
                del organizmy[x]


            if organizmy[x].getCzyRozmnazac() == 1: ##rozmnazam juz
                ktoryObieg = 0
                matka_x = organizmy[x].getPolozenie_x()
                matka_y = organizmy[x].getPolozenie_y()
                losuje_x = randint(-1, 1)
                losuje_y = randint(-1, 1)
                temp_x = 0
                temp_y = 0
                
                while True:
                    if ktoryObieg > 300:
                        break
                    if losuje_x != 0 or losuje_y != 0:
                        temp_x = losuje_x + matka_x
                        temp_y = losuje_y + matka_y
                        if 20 > temp_x >= 0 and 20 > temp_y >= 0:
                            break
                    losuje_x = randint(-1, 1)
                    losuje_y = randint(-1, 1)  
                    ktoryObieg += 1                      
                organizmy[x].setCzyRozmnazac(0)
                if organizmy[x] == None:
                    pass
                elif organizmy[x].getZnak() == "W":
                    dziecko = Wilk(temp_x, temp_y)
                elif organizmy[x].getZnak() == "O":
                    dziecko = Owca(temp_x, temp_y)
                elif organizmy[x].getZnak() == "L":
                    dziecko = Lew(temp_x, temp_y)
                elif organizmy[x].getZnak() == "S":
                    dziecko = Lis(temp_x, temp_y)
                elif organizmy[x].getZnak() == "K":
                    dziecko = Krowa(temp_x, temp_y)
                elif organizmy[x].getZnak() == "T":
                    dziecko = Trawa(temp_x, temp_y)
                elif organizmy[x].getZnak() == "G":
                    dziecko = Guarana(temp_x, temp_y)
                elif organizmy[x].getZnak() == "J":
                    dziecko = Jagoda(temp_x, temp_y)

                dodajDziecko(dziecko, organizmy, mapa_organizmow, temp_x, temp_y)
                print(dziecko.getZnak(), "rozmnozylo sie")


        def rysujSwiat(mapa_organizmow, pola_mapy, root):
            for x in range(20):
                for y in range(20):
                        if mapa_organizmow[x][y] == None or mapa_organizmow[x][y].getZnak() == ".":
                            pola_mapy[x][y]["text"] = "    " 
                        else:
                            pola_mapy[x][y]["text"] =  mapa_organizmow[x][y].getZnak()
            root.mainloop() 
                   
        rysujSwiat(mapa_organizmow, pola_mapy, root)




    wilk2 = Wilk(4, 5)
    wilk3 = Wilk(5, 4)
    owca = Owca(5, 5)
    owca1 = Owca(10, 10)
    lis = Lis(12, 15)
    lis2 = Lis(7, 8)
    lew = Lew(3, 8)
    lew2 = Lew(16, 16)
    krowa = Krowa(19, 19)
    krowa2 = Krowa(18, 18)
    trawa = Trawa(8, 8)
    guarana = Guarana(3, 3)
    jagoda = Jagoda(14, 14)


    dodajZwierze(wilk2, organizmy, mapa_organizmow)
    dodajZwierze(wilk3, organizmy, mapa_organizmow)
    dodajZwierze(owca, organizmy, mapa_organizmow)
    dodajZwierze(owca1, organizmy, mapa_organizmow)
    dodajZwierze(lew, organizmy, mapa_organizmow)
    dodajZwierze(lew2, organizmy, mapa_organizmow)
    dodajZwierze(lis, organizmy, mapa_organizmow)
    dodajZwierze(lis2, organizmy, mapa_organizmow)
    dodajZwierze(krowa, organizmy, mapa_organizmow)
    dodajZwierze(krowa2, organizmy, mapa_organizmow)
    dodajZwierze(trawa, organizmy, mapa_organizmow)
    dodajZwierze(guarana, organizmy, mapa_organizmow)
    dodajZwierze(jagoda, organizmy, mapa_organizmow)

    root = Tk()

    root.title("Swiat Dzungli")
    root.geometry("800x650")

    app = Frame(root)
    app.grid()

    for x in range(20):
        for y in range(20):
                        if mapa_organizmow[x][y].getZnak() is ".":
                            pola_mapy[x][y] = Button(app, text = "    ")
                            pola_mapy[x][y].grid(column = x, row = y)
                        else:
                            pola_mapy[x][y] = Button(app, text = mapa_organizmow[x][y].getZnak()) 
                            pola_mapy[x][y].grid(column = x, row = y)

    wskaznik = functools.partial(akcja, organizmy, mapa_organizmow, pola_mapy, root)
    nowaTura = Button(app, text = "Nowa Tura")
    nowaTura.grid(column = 25)
    nowaTura["command"] = wskaznik
    listaZapisu = []
    


    def zapisujemy(listaZapisu, organizmy, mapa_organizmow):
        outFile = open('zapis.txt', 'w')
        lita = []
        for x in range(20):
            for y in range(20):
                if mapa_organizmow[x][y] != None or mapa_organizmow[x][y].getZnak() != ".":
                    

                    listaZapisu.append(str(x))
                    listaZapisu.append(' ')
                    listaZapisu.append(str(y))
                    listaZapisu.append(' ')
                    listaZapisu.append(str(mapa_organizmow[x][y].getZnak()))
                    listaZapisu.append(' ')
                    listaZapisu.append(str(mapa_organizmow[x][y].getInicjatywa()))
                    listaZapisu.append(' ')
                    listaZapisu.append(str(mapa_organizmow[x][y].getSila()))
                    listaZapisu.append('\n')
                    tekst = ''.join(listaZapisu)
                    outFile.write(tekst)
        outFile.close()

    def wczytujemy(organizmy, mapa_organizmow, wskaznik, root, pola_mapy):
        def rysujSwiat(mapa_organizmow, pola_mapy, root):
            for x in range(20):
                for y in range(20):
                        if mapa_organizmow[x][y] == None or mapa_organizmow[x][y].getZnak() == ".":
                            pola_mapy[x][y]["text"] = "    " 
                        else:
                            pola_mapy[x][y]["text"] =  mapa_organizmow[x][y].getZnak()
            root.mainloop()         
        
        for x in range(20):
            for y in range(20):
                mapa_organizmow[x][y] = None

        del organizmy[ : ]
        #outFile = open('zapis.txt', 'r')
        try:
            outFile = open('zapis.txt', 'r')
        except ZeroDivisionError:
            print("Nic tu nie ma")
        finally:
            print("Daruje ci ten czas")

        for line in outFile:
            spacja = []
            spacja = line.split(' ')

            x = int(spacja[0])
            y = int(spacja[1])
            znak = spacja[2]
            #print(znak)
            inicjatywa = int(spacja[3])
            sila = int(spacja[4])

            if znak == 'O':
                mapa_organizmow[x][y] = Owca(x, y)
                mapa_organizmow[x][y].setSila(sila)
                mapa_organizmow[x][y].setInicjatywa(inicjatywa)
                mapa_organizmow[x][y].setZnak(znak)
                organizmy.append(mapa_organizmow[x][y])
            elif znak == 'W':
                mapa_organizmow[x][y] = Wilk(x, y)
                mapa_organizmow[x][y].setSila(sila)
                mapa_organizmow[x][y].setInicjatywa(inicjatywa)
                mapa_organizmow[x][y].setZnak(znak)
                organizmy.append(mapa_organizmow[x][y])
            elif znak == 'L':
                mapa_organizmow[x][y] = Lew(x, y)
                mapa_organizmow[x][y].setSila(sila)
                mapa_organizmow[x][y].setInicjatywa(inicjatywa)
                mapa_organizmow[x][y].setZnak(znak)
                organizmy.append(mapa_organizmow[x][y])
            elif znak == 'L':
                mapa_organizmow[x][y] = Lis(x, y)
                mapa_organizmow[x][y].setSila(sila)
                mapa_organizmow[x][y].setInicjatywa(inicjatywa)
                mapa_organizmow[x][y].setZnak(znak)
                organizmy.append(mapa_organizmow[x][y])
            elif znak == 'K':
                mapa_organizmow[x][y] = Krowa(x, y)
                mapa_organizmow[x][y].setSila(sila)
                mapa_organizmow[x][y].setInicjatywa(inicjatywa)
                mapa_organizmow[x][y].setZnak(znak)
                organizmy.append(mapa_organizmow[x][y])
            elif znak == 'T':
                mapa_organizmow[x][y] = Trawa(x, y)
                mapa_organizmow[x][y].setSila(sila)
                mapa_organizmow[x][y].setInicjatywa(inicjatywa)
                mapa_organizmow[x][y].setZnak(znak)
                organizmy.append(mapa_organizmow[x][y])
            elif znak == 'G':
                mapa_organizmow[x][y] = Guarana(x, y)
                mapa_organizmow[x][y].setSila(sila)
                mapa_organizmow[x][y].setInicjatywa(inicjatywa)
                mapa_organizmow[x][y].setZnak(znak)
                organizmy.append(mapa_organizmow[x][y])
            elif znak == 'J':
                mapa_organizmow[x][y] = Jagoda(x, y)
                mapa_organizmow[x][y].setSila(sila)
                mapa_organizmow[x][y].setInicjatywa(inicjatywa)
                mapa_organizmow[x][y].setZnak(znak)
                organizmy.append(mapa_organizmow[x][y])
            
        rysujSwiat(mapa_organizmow, pola_mapy, root)
        outFile.close()



    #print (listaZapisu)
    Zapisz = Button(app, text = "Zapisz")
    Zapisz.grid(column = 25)
    wskaznikZapisu = functools.partial(zapisujemy, listaZapisu, organizmy, mapa_organizmow)

    Zapisz["command"] = wskaznikZapisu

    Wczytaj = Button(app, text = "Wczytaj")
    wskaznikWczytu = functools.partial(wczytujemy, organizmy, mapa_organizmow, wskaznik, root, pola_mapy)
    Wczytaj.grid(column = 25)
    Wczytaj['command'] = wskaznikWczytu

    root.mainloop()

   
