#include <iostream>
using namespace std;

int main()
{
	long double pi = 3.14159265358979153846;
	long double wartosc;
	long double porownanie;
	int wynik_modulo;
	long double modulo;
	long double wynik;
	cout.precision(32);
	cout << "Wprowadz wartosc:" << endl;
	cin >> wartosc;
	cout << endl;

	

	porownanie = wartosc;
	wynik_modulo = porownanie / pi;

	modulo = porownanie - (wynik_modulo * pi);

	wartosc = wartosc*pi / 180;

	cout << "Wynik: " << endl;

	if (modulo == 0 || modulo == pi)
		cout << 0 << endl;
	else if (modulo == pi / 2)
		cout << 1 << endl;
	else if (modulo > 0 && modulo < pi)
	{
		long double x = wartosc;
		wynik = ((-4) / (pi * pi)) * wartosc * wartosc + (4 / pi) * wartosc;
		
		cout << wynik << endl;
	}
	else if (modulo > pi && modulo < 2 * pi)
	{
		long double x_kwadrat = wartosc * wartosc;
		long double x = wartosc;
		wynik = ((4 / (pi * pi)) * x_kwadrat) - ((12/pi) * x) + 8;
		cout << wynik << endl;
	}




	system("pause");
	return 0;
}