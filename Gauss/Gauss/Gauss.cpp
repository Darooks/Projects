#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>

using namespace std;

int main()
{
	ofstream plik;
	plik.open("taylor.txt", ios::app);

	clock_t s, f;
	double czas = 0;
	


	srand(time(NULL));
	const char zmienna = 'x';
	int eqn_num = 0, x = 0, y = 0, matrix_size = 0;
	double a = 0, b = 0;
	//char q;
	cout << "Ile ma byc wartosci w macierzy n x n: " << endl;
	cin >> eqn_num;
	cout << endl;
	y = eqn_num;
	x = y + 1;

	vector < vector<double>> matrix(y, vector <double>(x, 0));

	for (int iy = 0; iy < y; iy++)
	{
		double coef = 0;
		for (int ix = 0; ix < x; ix++)
		{
			coef = (double)rand()/rand();///rand();
			matrix[iy][ix] = coef;
		}
	}
	cout << "Macierz: " << endl;
	/*for (int iy = 0; iy < y; iy++)
	{
		for (int ix = 0; ix < x; ix++)
			cout << matrix[iy][ix] << " ";
		cout << endl;
	}*/
	s = clock();
	for (int ix = 0; ix < x; ix++)
	{
		for (int iy = 0; iy < y; iy++)
		{
			double a = matrix[iy][ix];
			if (iy == ix)
			{
				double b = matrix[iy][iy];
				for (int iix = 0; iix < x; iix++)
					matrix[iy][iix] = matrix[iy][iix] / b;
			}
			else if (iy > ix && matrix[iy][ix] != 0)
			{
				for (int iix = 0; iix < x; iix++)
				{
					b = matrix[ix][iix] * a;
					matrix[iy][iix] = b - matrix[iy][iix];
				}
			}
		}
	}

	/*for (int ix = 0; ix < x; ix++)
	{
		for (int iy = 0; iy < y; iy++)
		{
			double a = matrix[iy][ix];
			if (iy < ix && matrix[iy][ix] != 0 && ix < y)
			{
				for (int iix = 0; iix < x; iix++)
				{
					double b = matrix[ix][iix] * a;
					matrix[iy][iix] = matrix[iy][iix] - b;
					b = 0;
				}
			}
		}
	}*/
	for (int ix = x - 1; ix >= 0; ix--)
	{
		for (int iy = y - 1; iy >= 0; iy--)
		{
			double a = matrix[iy][ix];
			if (iy < ix && matrix[iy][ix] != 0 && ix < y)
			{
				for (int iix = x - 1; iix >= 0; iix--)
				{
					double b = matrix[ix][iix] * a;
					matrix[iy][iix] = matrix[iy][iix] - b;
					b = 0;
				}
			}
		}
	}
	cout << endl;
	for (int iy = 0; iy < y; iy++)
	{
		cout << "x" << iy + 1 << " = " << matrix[iy][y] << endl;
	}

	f = clock();
	czas = (double)(f - s) / (double)(CLOCKS_PER_SEC);
	cout << czas << endl;
	plik << eqn_num << " " << czas << endl;

	plik.close();
	system("pause");
	return 0;
}