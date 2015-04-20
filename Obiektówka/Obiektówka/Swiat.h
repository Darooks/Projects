#pragma once
#include "Organizm.h"
using namespace std;

class Swiat
{
protected:
	Organizm *organizmy[400];
	Organizm *czytaj_organizm[20][20];
	int ilosc_organizmow;

public:
	Swiat() 
	{ 
		ilosc_organizmow = 0;
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				czytaj_organizm[i][j] = NULL;
			}
		}

		for (int i = 0; i < 400; i++)
		{
			organizmy[i] = NULL;
		}
	};

	~Swiat() { };

	void dodaj_zwierze(Zwierze *wsk_zwierze)
	{
		int pozycja_x = wsk_zwierze->polozenie_x;
		int pozycja_y = wsk_zwierze->polozenie_y;
		czytaj_organizm[pozycja_y][pozycja_x] = wsk_zwierze;
		organizmy[ilosc_organizmow] = czytaj_organizm[pozycja_y][pozycja_x];
		ilosc_organizmow++;
	}

	void sortuj(Organizm *wsk_organizm[])
	{
		for (int i = ilosc_organizmow - 1; i > 0; i--)
		{
			for (int j = 0; j < i; j++)
			{
				if (organizmy[j]->inicjatywa < organizmy[j + 1]->inicjatywa)
				{
					swap(organizmy[j], organizmy[j + 1]);
				}
			}
		}
	}
	
	void wykonajTure()
	{
		system("cls");
		sortuj(organizmy);

		for (int i = 0; i < ilosc_organizmow; i++)
		{
			organizmy[i]->akcja(czytaj_organizm, organizmy[i]->polozenie_x, organizmy[i]->polozenie_y, ilosc_organizmow, organizmy, i, this);

			if (organizmy[i]->rozmnozenie == 1)
			{
				int pozycja_x = organizmy[i]->polozenie_x;
				int pozycja_y = organizmy[i]->polozenie_y;
				char symbol = organizmy[i]->znak;

				int ruchx = rand() % 3;
				int ruchy = rand() % 3;
/////////////////////////////////////////////////////////
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

						int pomocnicze_x = pozycja_x + ruchx;
						int pomocnicze_y = pozycja_y + ruchy;

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

				switch (symbol)
				{
					case 'W':
					{
						Zwierze *dziecko_wilka = new Wilk(pozycja_x, pozycja_y, this);
						dodaj_zwierze(dziecko_wilka);
						break;
					}
					case 'O':
					{
						Zwierze *dziecko_owieczki = new Owca(pozycja_x, pozycja_y, this);
						dodaj_zwierze(dziecko_owieczki);
						break;
					}
				}
			}
		}
		//void akcja(Organizm *czytajOrganizm[20][20], int polozenie_x, int polozenie_y, int ilosc_organizmow);
		//(Swiat wsk_swiat, int polozenie_x, int polozenie_y, int ilosc_organizmow, Organizm *czytajOrganizm[20][20]
	}

	void rysujSwiat()
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (czytaj_organizm[i][j] == NULL)
				{
					cout << ".";
				}
				else
				{
					czytaj_organizm[i][j]->rysowanie();
				}
			}
			cout << endl;
		}
	}

};