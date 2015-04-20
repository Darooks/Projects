#pragma once

class Swiat;

class Organizm
{
public:
	//referencja do klasy swiat

	virtual void akcja(Organizm *czytaj_organizm[20][20], int polozenie_x, int polozenie_y, int ilosc_organizmow, Organizm *organizmy[], int ktory, Swiat *wsk_swiat) = 0;
	virtual void kolizja(Organizm *czytaj_organizm[20][20], int polozenie_x, int polozenie_y, int ilosc_organizmow, Organizm *organizmy[], int ktory, Swiat *wsk_swiat, int ruchx, int ruchy) = 0;
	virtual void rysowanie() = 0;
	//8, 8, wsk_Swiat
	//Plansze, miejsce, organizmy, ilosc organizmow, wspolrzedne na ktore wchodzisz

	char znak;
	Swiat *tura;
	int sila;
	int inicjatywa;
	int polozenie_y;
	int polozenie_x;
	bool rozmnozenie;
	bool smierc;
	int wiek;
	bool zwierzak;

	Organizm()
	{
		//zwierzak = 0;
	}

	void ustawWartosc(char atrybut[], int wartosc)
	{
		if (!strcmp(atrybut, "polozeniex"))
		{
			this->polozenie_x = wartosc;
		}
		else if (!strcmp(atrybut, "polozeniey"))
		{
			this->polozenie_y = wartosc;
		}
		else if (!strcmp(atrybut, "rozmnozenie"))
		{
			this->rozmnozenie = wartosc;
		}
	}

};

#include "Zwierze.h"
#include "Roslina.h"