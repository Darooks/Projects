#include <iostream>
#include <math.h>
using namespace std;

#define przedzial 1

double moja_funkcja(double x)
{
	double wynik = sin(x) / x;
	//double wynik = (x*x*x) + (4 * x*x) - 10;

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
	int ilosc_x = 5;
	double temp_a = a;
	double temp_b = b;
	bool jest_x = true;
	int licznik = 0;
	
	//b = a + 0.1;
	b = a + przedzial;
	while (true)
	{
		//b = a + 2.0;
		if (a >= temp_b || b > temp_b)
			break;
		for (int i = 0; i < it_end; i++)
		{
			c = a + ((b - a) / 2);
			x = c;

			//cout << "a" << i + 1 << " = " << a << endl;
			//cout << "b" << i + 1 << " = " << b << endl;
			//cout << "x" << i + 1 << " = " << x << endl;
			//cout << "f(x)" << i + 1 << " = " << moja_funkcja(x) << endl;
			//cout << endl;

			if (moja_funkcja(a)*moja_funkcja(x) < 0)
			{
				b = x;
				jest_x = true;
			}
			else if (moja_funkcja(b)*moja_funkcja(x) < 0)
			{
				a = x;
				jest_x = true;
			}
			else
				jest_x = false;
		}
		licznik++;
		if (jest_x == true)
		{
			cout << "x" << " = " << x << endl;
			cout << endl;
		}
		
		//a = temp_a + (3.0*(double)j);
		//a = x;
		//b += 0.1;
		//a = temp_a;
		a = temp_a + (przedzial*(double)licznik);
		b = a + przedzial;
	}

}

void stycznych(double x, int iter)
{
	double x_n, y, dy;
	double eps = 0.0005;
	int iter_max = 20;
	x_n = x - 1;
	y = moja_funkcja(x);
	while (abs(x_n - x) > eps && abs(y) > eps)
	{
		//dy = (fun(x + eps) - y) / eps;
		dy = moja_funkcja_pochodna(x);

		if (abs(dy) < eps || iter++ >= iter_max)
		{
			cout << iter_max << endl;
			return;
		}

		x_n = x;
		x = x - y / dy;
		y = moja_funkcja(x);
		cout << x << endl;

	}
	cout << iter_max << endl;
	return;
}

int main()
{
	double a = 2.0;
	double b = 10.0;
	double eps = 0.0005;
	int iter = 20;

	//for (int i = 1; i <= 6; i++)
	//{
	//	
	//bisekcja(a, b, iter, eps);
	stycznych(1, 0);
	//	a += 3;
	//	b += 3;
	//}

	system("pause");
	return 0;
}