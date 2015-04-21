#include <iostream>
#include <math.h>
using namespace std;

double moja_funkcja(double x)
{
	//double wynik = (sin(x)) / x;
	double wynik = (x*x*x) + (4 * x*x) - 10;

	return wynik;
}

double moja_funkcja_pochodna(double x) // x(3x + 8)
{										// (x*cos(x) - sin(x)) / x^2
	double wynik = x*((3 * x) + 8);
	//double wynik = ((x*cos(x)) - sin(x)) / x *x;
	return wynik;
}

void bisekcja(double a, double b, int it_end, double eps)
{
	double c;
	double x;

	for (int i = 0; i < it_end; i++)
	{
		c = a + ((b - a) / 2);
		x = c;

		cout << "a" << i + 1 << " = " << a << endl;
		cout << "b" << i + 1 << " = " << b << endl;
		cout << "x" << i + 1 << " = " << x << endl;
		cout << "f(x)" << i + 1 << " = " << moja_funkcja(x) << endl;
		cout << endl;

		if (moja_funkcja(a)*moja_funkcja(x) < 0)
			b = x;
		else
			a = x;
	}
	

}

void styczne(double x0, double x1, double eps)
{

}

int main()
{
	double a = 1;
	double b = 2;
	double eps = 0.0005;
	int iter = 20;

	bisekcja(a, b, iter, eps);

	system("pause");
	return 0;
}