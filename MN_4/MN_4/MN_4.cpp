#include <iostream>
#include <math.h>
using namespace std;

#define przedzial 1
double eps = 0.000001;

double fun0(double x)
{
	double wynik = sin(x) / x;
	//double wynik = (x*x*x) + (4 * x*x) - 10;

	return wynik;
}

double fun0_d(double x) // x(3x + 8)
{										// (x*cos(x) - sin(x)) / x^2
	//double wynik = x*((3 * x) + 8);
	double wynik = ((x*cos(x)) - sin(x)) / x *x;
	return wynik;
}

double fun1(double x)
{
	return (x - 1)*(x - 2)*(x - 3)*(x - 4);
}

void bisekcja(double a, double b, int it_end)
{
	double c;
	double x;
	int ilosc_x = 5;
	double temp_a = a;
	double temp_b = b;
	bool jest_x = true;
	int licznik = 0;
	
	b = a + przedzial;
	while (true)
	{
		if (a >= temp_b || b > temp_b)
			break;
		for (int i = 0; i < it_end; i++)
		{
			c = a + ((b - a) / 2);
			x = c;

			if (fun0(a)*fun0(x) < 0)
			{
				b = x;
				jest_x = true;
			}
			else if (fun0(b)*fun0(x) < 0)
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
		
		a = temp_a + (przedzial*(double)licznik);
		b = a + przedzial;
	}

}

void stycznych(double x, int iter)
{
	double x_n, y, dy;
	int iter_max = 200;
	x_n = x - 1;
	y = fun0(x);
	while (abs(x_n - x) > eps && abs(y) > eps)
	{
		//dy = (fun(x + eps) - y) / eps;
		dy = fun0_d(x);

		if (abs(dy) < eps || iter++ >= iter_max)
		{
			cout << iter_max << endl;
			return;
		}

		x_n = x;
		x = x - y / dy;
		y = fun0(x);
	}
	cout << x << endl;
	//cout << dy << endl;
	return;
}

int main()
{
	double a = 2.0;
	double b = 10.0;
	//double eps = 0.0005;
	int iter = 20;

	//bisekcja(a, b, iter, eps);
	for (int i = 1; i <= 10; i++)
		stycznych(i, 0);

	system("pause");
	return 0;
}