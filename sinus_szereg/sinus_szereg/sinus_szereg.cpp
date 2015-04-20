#include <iostream> 
#include <fstream>
#include <cmath>
#include <math.h> 
#include <cmath>
using namespace std;
//--------------------------------------------------------------------------- 
#define ilosc 30
//const int ilosc = 30;

long double silnia_mian(long double n)
{
	if (n == 0)
		return 1;

	return n*silnia_mian(n - 1);
}

long double taylor(long double x)
{
	long double pi = 3.14159265358979323846;
	x = x*pi / 180;
	int minus_jeden = -1;
	long double licznik;
	long double mianownik;
	long double wynik = 0;

	for (int i = 0; i < ilosc; i++)
	{
		if (i % 2 == 0)
			minus_jeden = 1;
		else
			minus_jeden = -1;

		licznik = x;
		for (int j = 1; j < (2 * i) + 1; j++)
		{
			licznik *= x;
		}
		mianownik = silnia_mian(2*i+1);

		wynik += (minus_jeden*licznik) / mianownik;
		//cout << minus_jeden << " * " << licznik << " / " << mianownik << endl;
	}
	return wynik;
}

long double z_dolu(long double x)
{
	long double pi = 3.14159265358979323846;
	x = x*pi / 180;
	long double tab[ilosc];
	long double wynik = 0;
	tab[0] = x;
	for (int i = 1; i < ilosc; i++)
	{
		tab[i] = (-(x*x) / (2 * i * (2 * i + 1))) * tab[i - 1];
	}

	for (int i = 0; i < ilosc; i++)
		wynik += tab[i];

	return wynik;
}

long double z_gory(long double x)
{
	

	long double pi = 3.14159265358979323846;
	x = x*pi / 180;
	long double tab[ilosc];
	long double wynik = 0;
	tab[0] = x;
	for (int i = 1; i < ilosc; i++)
	{
		tab[i] = (-(x*x) / (2 * i * (2 * i + 1))) * tab[i - 1];
	}
	
	for (int i = ilosc - 1; i >= 0; i--)
		wynik += tab[i];

	return wynik;
}

int main()
{
	
	ofstream plik;
	plik.precision(32);
	//ofstream plik2;
	//ofstream plik3;
	//ofstream plik4;
	plik.open("z_dolu.txt", ios::app);
	//plik2.open("od_gory.txt", ios::app);
	//plik3.open("od_dolu.txt", ios::app);
	//plik4.open("std.txt", ios::app);
	long double pi = 3.14159265358979323846;
	long double i = 75;

		long double liczba;
		long double wynik;

		//cout << "Podaj wartosc" << endl;
		//cin >> liczba;
		cout.precision(32);
		cin.precision(32);

		//wynik = taylor(liczba);																	//
		cout << "Stopnie: " << i << endl;															//z dolu
		cout << "Taylor      : " << taylor(i) << endl;												//z gory
		//plik << ilosc << endl;
		//plik << fabs(sin(i*pi / 180) - taylor(i)) << endl;
		plik << fabs(sin(i*pi / 180) - z_dolu(i));
		//plik << fabs(sin(i*pi / 180) - z_gory(i)) << endl;
		//plik << "Sinus: " << sin(i*pi / 180) << endl;
		plik << endl;
		cout << "Wzor z dolu: " << z_dolu(i) << endl;

		cout << "Wzor z gory: " << z_gory(i) << endl;
		cout << "Lib:       : " << sin(i*pi / 180) << endl;
		cout << "Sprawdz " << fabs(sin(i*pi / 180) - z_gory(i)) - fabs(sin(i*pi / 180) - z_dolu(i));
		cout << endl;
	
	plik.close();
	//plik2.close();
	//plik3.close();
	//plik4.close();

	system("pause");
	return 0;
}