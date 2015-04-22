#include <iostream>
#include <math.h>
using namespace std;

#define przedzial 0.1
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
	double wynik = ((x*cos(x)) - sin(x)) / (x * x);
	return wynik;
}

double fun1(double x)
{
	return (x - 1)*(x - 2)*(x - 3)*(x - 4);
}

double fun2(double x)
{
	return tan(x);
}
double fun2_d(double x)
{
	return 1 + tan(x) * tan(x);
}

double fun3(double x)
{
	return (x - 1)*(x - 2)*(x - 3)*(x - 4);
}
double fun3_d(double x)
{
	return 4 * x * x * x - 30 * x * x + 70 * x - 50;
}

double fun4(double x)
{
	return (x - 0.01)*(x - 0.02)*(x - 0.03)*(x - 0.04);
}
double fun4_d(double x)
{
	return (80000 * x * x * x - 6000 * x * x + 140 * x - 1) / 20000;
}

double fun5(double x)
{
	return x*x*x*x;
}

double fun5_d(double x)
{
	return 4 * (x*x*x);
}

void bisekcja(double a, double b, int it_end)
{
	double c;
	double x = 0;
	int ilosc_x = 5;
	double temp_a = a;
	double temp_b = b;
	bool jest_x = true;
	int licznik = 0;
	
	b = a + przedzial;
	while (fabs(a - b) > eps)
	{

		if (a >= temp_b || b > temp_b)
			break;
		for (int i = 0; i < it_end; i++)
		{
			c = a + ((b - a) / 2);
			x = c;
			/*if (abs(fun0((a + b) / 2)) < eps)
			{
				jest_x = false;
				break;
			}*/
			if (fun5(a)*fun5(x) < 0)
			{
				b = x;
				jest_x = true;
			}
			else if (fun5(b)*fun5(x) <= 0)
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
			cout << "x = " << x << endl;
			cout << endl;
		}
		
		a = temp_a + (przedzial*(double)licznik);
		b = a + przedzial;
		
	}
}

void stycznych(double x)
{
	int iter = 0;
	double x_n, y, dy;
	int iter_max = 200;
	x_n = x - 1;
	y = fun5(x);
	while (abs(x_n - x) > eps && abs(y) > eps)
	{
		//dy = (fun(x + eps) - y) / eps;
		dy = fun5_d(x);

		if (abs(dy) < eps || iter++ >= iter_max)
		{
			cout << iter_max << endl;
			return;
		}

		x_n = x;
		x = x - y / dy;
		y = fun5(x);
	}

	cout << x << endl;
	//cout << dy << endl;
	return;
}

int main()
{
	double a = 0.0;
	double b = 13.0;
	//double eps = 0.0005;
	int iter = 20;
	

	bisekcja(a, b, iter);
	/*for (double i = -1.0; i <= 1.0; i += 0.1)
		stycznych(i);
*/
	system("pause");
	return 0;
}