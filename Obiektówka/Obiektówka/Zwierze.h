#pragma once

//#include "Organizm.h"
using namespace std;

class Zwierze : public Organizm
{
public:
	Zwierze() {};
	~Zwierze() {};
	void akcja(Organizm *czytaj_organizm[20][20], int polozenie_x, int polozenie_y, int ilosc_organizmow, Organizm *organizmy[], int ktory, Swiat *wsk_swiat);
	void kolizja(Organizm *czytaj_organizm[20][20], int polozenie_x, int polozenie_y, int ilosc_organizmow, Organizm *organizmy[], int ktory, Swiat *wsk_swiat, int ruchx, int ruchy);
	void rysowanie();
};
//Plansze, miejsce, organizmy, ilosc organizmow, wspolrzedne na ktore wchodzisz
void Zwierze::rysowanie()
{
	cout << this->znak;
}

void Zwierze::akcja(Organizm *czytaj_organizm[20][20], int pozycja_x, int pozycja_y, int ilosc_organizmow, Organizm *organizmy[], int ktory, Swiat *wsk_swiat)
{
	int ruchx = rand() % 3;
	int ruchy = rand() % 3;
	//srand(time(NULL));
	//int ruchy = (rand() % 9);

	//      ruchx = ruchy;

	pozycja_x = this->polozenie_x;
	pozycja_y = this->polozenie_y;

	int pomocnicze_x = 0;
	int pomocnicze_y = 0;

	this->ustawWartosc("rozmnozenie", 0);

	while (true)
	{
		if (ruchx != 0 || ruchy != 0)
		{
			if (ruchx == 2)
			{
				ruchx = -1;
			}
			if (ruchy == 2)
			{
				ruchy = -1;
			}

			pomocnicze_x = pozycja_x + ruchx;
			pomocnicze_y = pozycja_y + ruchy;

			if ((pomocnicze_x >= 0 && pomocnicze_x < 20) && (pomocnicze_y >= 0 && pomocnicze_y < 20))
			{
				pozycja_x = pomocnicze_x;
				pozycja_y = pomocnicze_y;
				break;
			}
		}

		ruchx = rand() % 3;
		ruchy = rand() % 3;
	}

	if ((czytaj_organizm[pomocnicze_x][pomocnicze_y] != NULL))
	{
		Zwierze::kolizja(czytaj_organizm, polozenie_x/* - ruchx*/, polozenie_y /*- ruchy*/, ilosc_organizmow, organizmy, ktory, wsk_swiat, ruchx, ruchy);
	}

	if (czytaj_organizm[pomocnicze_x][pomocnicze_y] == NULL)
	{
		this->ustawWartosc("polozeniex", pozycja_x);
		this->ustawWartosc("polozeniey", pozycja_y);

		//czytaj_organizm[polozenie_x - ruchx][polozenie_y - ruchy] = czytaj_organizm[polozenie_x][polozenie_y];
		//czytaj_organizm[polozenie_x][polozenie_y] = NULL;

		czytaj_organizm[polozenie_x][polozenie_y] = czytaj_organizm[polozenie_x - ruchx][polozenie_y - ruchy];
		czytaj_organizm[polozenie_x - ruchx][polozenie_y - ruchy] = NULL;
		//cout << this->znak << " | " << polozenie_x << ", " << polozenie_y << endl;
	}
	
}
//Organizm *czytaj_organizm[20][20], int polozenie_x, int polozenie_y, int ilosc_organizmow, Organizm *organizmy[], int ktory
void Zwierze::kolizja(Organizm *czytaj_organizm[20][20], int polozenie_x, int polozenie_y, int ilosc_organizmow, Organizm *organizmy[], int ktory, Swiat *wsk_swiat, int ruchx, int ruchy)
{
	int pozycja_x = this->polozenie_x;
	int pozycja_y = this->polozenie_y;
	bool dzieciak = this->rozmnozenie;


	Organizm *skolidowany = czytaj_organizm[polozenie_x][polozenie_y];

	if (skolidowany->zwierzak == 1)
	{
		char atak = this->znak;
		char obrona = skolidowany->znak;

		if (atak == obrona) //PLODZENIE
		{
			this->ustawWartosc("rozmnozenie", 1);
		}
		else
		{
			int sila_atak = this->sila;
			int sila_obrona = skolidowany->sila;
			if (sila_atak < sila_obrona)
			{
				czytaj_organizm[pozycja_x][pozycja_y] = NULL;
			}
			else if (sila_atak >= sila_obrona)
			{
				czytaj_organizm[polozenie_x][polozenie_y] = czytaj_organizm[pozycja_x][pozycja_y];
				czytaj_organizm[pozycja_x][pozycja_y] = NULL;
				this->ustawWartosc("polozeniex", polozenie_x);
				this->ustawWartosc("polozeniey", polozenie_y);
			}
		}
	}
	else
	{

	}
}

#include "Wilk.h"
#include "Owca.h"