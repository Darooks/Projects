#include <iostream>
#include <fstream>

using namespace std;

//#define iteracja 160
#define przedzial 100
#define d 0.85

void Jacobi(double **matrix, double *b, int iteracja)//, double **L, double **D, double **U)
{
	int size = przedzial;

	double* N = new double[size];

	double** M = new double*[size];
	for (int i = 0; i < size; i++)
		M[i] = new double[size];

	for (int i = 0; i < size; i++)
		N[i] = 1 / matrix[i][i]; // D^-1

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++) //M = -D^-1 (L + U)
		{
			if (i == j)
				M[i][j] = 0;
			else
				M[i][j] = -(matrix[i][j] * N[i]);
		}
	}
	double *x1 = new double[size];
	for (int i = 0; i < size; i++)
		x1[i] = 0;

	double *x2 = new double[size];
	for (int i = 0; i < size; i++)
		x2[i] = 0;

	for (int k = 0; k < iteracja; k++)
	{
		for (int i = 0; i < size; i++)
		{
			x2[i] = N[i] * b[i];
			for (int j = 0; j < size; j++)
				x2[i] += M[i][j] * x1[j];
		}
		for (int i = 0; i < size; i++)
			x1[i] = x2[i];

	}

	for (int i = 0; i < przedzial - 4; i++)
		printf("x[%d] = %.20f\n", (i + 1), x1[i]);
	
}

void gauss_seidel(double **matrix, double *b, int iteracja)
{
	int size = przedzial;

	double** D = new double*[size];

	for (int i = 0; i < size; i++)
		D[i] = new double[size];

	double** L = new double*[size];

	for (int i = 0; i < size; i++)
		L[i] = new double[size];

	double** U = new double*[size];

	for (int i = 0; i < size; i++)
		U[i] = new double[size];

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i < j)
				U[i][j] = matrix[i][j];
			else if (i > j)
				L[i][j] = matrix[i][j];
			else
				D[i][j] = matrix[i][j];
		}
	}

	for (int i = 0; i < size; i++) //D^-1
		D[i][i] = 1 / D[i][i];

	for (int i = 0; i < size; i++) //D^-1 * b
		b[i] *= D[i][i];

	for (int i = 0; i < size; i++) //D^-1 * L
	{
		for (int j = 0; j < size; j++)
			L[i][j] *= D[i][i];
	}

	for (int i = 0; i < size; i++) // D^-1 * U
	{
		for (int j = i + 1; j < size; j++)
			U[i][j] *= D[i][i];
	}

	double *x1 = new double[size];
	for (int i = 0; i < size; i++)
		x1[i] = 0;

	for (int k = 0; k < iteracja; k++)
	{
		for (int i = 0; i < size; i++)	// x = D^-1*b -
		{
			x1[i] = b[i];
			for (int j = 0; j < i; j++)
				x1[i] -= L[i][j] * x1[j];    // D^-1*L * x -
			for (int j = i + 1; j < size; j++)
				x1[i] -= U[i][j] * x1[j];    // D^-1*U * x
		}
	}

	for (int i = 0; i < przedzial - 4; i++) 
		printf("x[%d] = %.20f\n", (i + 1), x1[i]);
	
}

void zrob_lista_sasiedztwa(double **tablica, double *ilosc_sasiedztwa)
{
	ifstream plik;
	plik.open("macierz2.txt");
	int ojciec;
	int sasiad;

	for (int i = 0; i < przedzial; i++)
	{
		for (int j = 0; j < przedzial; j++)
			tablica[i][j] = 0;
		ilosc_sasiedztwa[i] = 0;
	}

	while (!plik.eof())
	{
		plik >> ojciec;
		plik >> sasiad;

		if (ojciec < przedzial && sasiad < przedzial)
			tablica[ojciec][sasiad] = 1;
	}
	/*for (int i = 0; i < przedzial; i++)
	{
	for (int j = 0; j < przedzial; j++)
	cout << tablica[i][j] << " ";
	cout << endl;
	}*/
	plik.close();
}

void zamien_tablice_1(double **lista_sasiedztwa, double *ilosc_sasiedztwa)
{
	for (int i = 0; i < przedzial; i++)
	{
		if (ilosc_sasiedztwa[i] == 0)
		{
			for (int j = 0; j < przedzial; j++)
			{
				if (i == j)
					lista_sasiedztwa[i][j] = 0;
				else
					lista_sasiedztwa[i][j] = 1;
			}
		}
	}
}

void sprawdz_wiersze(double **lista_sasiedztwa, double *ilosc_sasiedztwa)
{
	int licznik = 0;

	for (int i = 0; i < przedzial; i++)
	{
		for (int j = 0; j < przedzial; j++)
		{
			if (lista_sasiedztwa[i][j] == 1)
				licznik++;
		}
		ilosc_sasiedztwa[i] = licznik;
		licznik = 0;
	}

	zamien_tablice_1(lista_sasiedztwa, ilosc_sasiedztwa);

	for (int i = 0; i < przedzial; i++)
	{
		for (int j = 0; j < przedzial; j++)
		{
			if (lista_sasiedztwa[i][j] == 1)
				licznik++;
		}
		ilosc_sasiedztwa[i] = licznik;
		licznik = 0;
	}
}

void wynies_prawdopodobienstwo(double **lista_sasiedztwa, double *ilosc_sasiedztwa)
{
	// A = A * (-d) / ilosc sasiedztwa
	//double d = 0.85;

	double **temp, **temp2;
	temp = new double*[przedzial];
	temp2 = new double*[przedzial];
	for (int i = 0; i < przedzial; i++)
	{
		temp[i] = new double[przedzial];
		temp2[i] = new double[przedzial];
		for (int j = 0; j < przedzial; j++)
		{
			temp[i][j] = 0;
			temp2[i][j] = 0;
		}
	}

	for (int i = 0; i < przedzial; i++)
		temp[i][i] = 1.0 / ilosc_sasiedztwa[i];

	for (int y = 0; y < przedzial; y++) {
		for (int x = 0; x < przedzial; x++) {
			for (int k = 0; k < przedzial; k++) {
				temp2[x][y] += (temp[x][k] * lista_sasiedztwa[k][y] * d);
			}
		}
	}

	for (int y = 0; y < przedzial; y++) {
		for (int x = 0; x < przedzial; x++) {
			lista_sasiedztwa[y][x] = temp2[y][x];
		}
	}
}

void stworz_jednostkowa(double **lista_jednostkowa)
{
	for (int i = 0; i < przedzial; i++)
	{
		for (int j = 0; j < przedzial; j++)
		{
			if (i == j)
				lista_jednostkowa[i][j] = 1.0;
			else
				lista_jednostkowa[i][j] = 0.0;
		}
	}
}

void odejmij_jednostkowa(double **lista_sasiedztwa, double **lista_jednostkowa)
{
	for (int i = 0; i < przedzial; i++)
	{
		for (int j = 0; j < przedzial; j++)
		{
			lista_sasiedztwa[i][j] = lista_jednostkowa[i][j] - lista_sasiedztwa[i][j];
		}
	}
}

void stworz_wynikowa(double *lista_wynikowa)
{
	for (int i = 0; i < przedzial; i++)
		lista_wynikowa[i] = (1.0 - d) / przedzial;
}

bool sprawdz_zbieznosz(double **lista_sasiedztwa)
{
	int przek;
	int wartosci = 0;

	for (int i = 0; i < przedzial; i++)
	{
		for (int j = 0; j < przedzial; j++)
		{
			if (i == j)
			{
				przek = fabs(lista_sasiedztwa[i][j]);
				if (przek == 0)
					return false;
			}
			else
				wartosci += fabs(lista_sasiedztwa[i][j]);
			if (wartosci >= przek)
				return false;
		}
	}
	return true;
}

int main()
{
	double **lista_sasiedztwa, *ilosc_sasiedztwa, **lista_jednostkowa, *lista_wynikowa, **temp, *temp2;
	lista_sasiedztwa = new double*[przedzial];
	ilosc_sasiedztwa = new double[przedzial];
	lista_jednostkowa = new double*[przedzial];
	lista_wynikowa = new double[przedzial];
	temp = new double*[przedzial];
	temp2 = new double[przedzial];
	for (int i = 0; i < przedzial; i++)
	{
		lista_sasiedztwa[i] = new double[przedzial];
		lista_jednostkowa[i] = new double[przedzial];
		temp[i] = new double[przedzial];
	}
	stworz_jednostkowa(lista_jednostkowa);

	zrob_lista_sasiedztwa(lista_sasiedztwa, ilosc_sasiedztwa);
	sprawdz_wiersze(lista_sasiedztwa, ilosc_sasiedztwa);
	wynies_prawdopodobienstwo(lista_sasiedztwa, ilosc_sasiedztwa);
	odejmij_jednostkowa(lista_sasiedztwa, lista_jednostkowa);
	stworz_wynikowa(lista_wynikowa);

	double *x1 = new double[przedzial];
	for (int i = 0; i < przedzial; i++)
		x1[i] = 0;

	if (sprawdz_zbieznosz)
	{
		for (int i = 10; i <= 120; i += 10)
		{
			for (int y = 0; y < przedzial; y++)
			{
				for (int x = 0; x < przedzial; x++)
				{
					temp[y][x] = lista_sasiedztwa[y][x];
				}
				temp2[y] = lista_wynikowa[y];
			}
			Jacobi(lista_sasiedztwa, lista_wynikowa, i);
			cout << "--------- " << i << " ----------" << endl;
			//gauss_seidel(lista_sasiedztwa, lista_wynikowa, i);
			system("pause");
			for (int y = 0; y < przedzial; y++)
			{
				for (int x = 0; x < przedzial; x++)
				{
					lista_sasiedztwa[y][x] = temp[y][x];
				}
				lista_wynikowa[y] = temp2[y];
			}
		}
	}
	//system("pause");
	return 0;
}