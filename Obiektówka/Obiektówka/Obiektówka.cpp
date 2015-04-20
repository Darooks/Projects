#include <iostream>
#include <time.h>
#include <algorithm>
#include <stdlib.h> 
#include "Swiat.h"

using namespace std;

int main()
{
	srand(time(NULL));

	Swiat *wsk_Swiat = new Swiat;
	Zwierze *wilk3 = new Wilk(1, 1, wsk_Swiat);
	Zwierze *owca = new Owca(6, 6, wsk_Swiat);
	Zwierze *owieczka = new Owca(19, 19, wsk_Swiat);
	Zwierze *wilk = new Wilk(10, 10, wsk_Swiat);
	Zwierze *wilk2 = new Wilk(2, 2, wsk_Swiat);
	Zwierze *wilk4 = new Wilk(8, 8, wsk_Swiat);

	wsk_Swiat->dodaj_zwierze(owieczka);
	wsk_Swiat->dodaj_zwierze(wilk4);
	wsk_Swiat->dodaj_zwierze(wilk3);
	wsk_Swiat->dodaj_zwierze(owca);
	wsk_Swiat->dodaj_zwierze(wilk);
	wsk_Swiat->dodaj_zwierze(wilk2);
	//wsk_Swiat->dodaj_zwierze(owca2);
	wsk_Swiat->rysujSwiat();

	while (getchar() != EOF)
	{
		wsk_Swiat->wykonajTure();
		wsk_Swiat->rysujSwiat();
	}

	return 0;
}