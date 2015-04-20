#include <iostream>
#include <math.h>
using namespace std;

double moja_funkcja(double x)
{
	//double wynik = (sin(x)) / x;
	double wynik = (x*x*x) + (4 * x*x) - 10;

	return wynik;
}

void bisekcja(double a, double b, int it_end, double eps)
{
	double err = eps + 1;
	//double it_start = 0;
	double c;
	double x;

	double** x_vext = new double*[it_end];
	double** fx = new double*[it_end];
	double** xdif = new double*[it_end];

	int indeks;

	for (int i = 0; i < it_end; i++)
	{
		x_vext[i] = new double[it_end];
		fx[i] = new double[it_end];
		xdif[i] = new double[it_end];
	}

	for (int i = 0; i < it_end; i++)
	{
		c = a + ((b - a) / 2);
		x = c;

		cout << "a" << i + 1 << " = " << a << endl;
		cout << "b" << i + 1 << " = " << b << endl;
		cout << "x" << i + 1 << " = " << x << endl;
		cout << "f(x)" << i + 1 << " = " << moja_funkcja(x) << endl;
		cout << endl;

		//a = moja_funkcja(a);
		//b = moja_funkcja(b);
		//x = moja_funkcja(x);

		if (moja_funkcja(a)*moja_funkcja(x) < 0)
			b = x;
		else
			a = x;
	}
	

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