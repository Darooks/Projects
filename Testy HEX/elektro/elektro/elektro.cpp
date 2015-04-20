#include <iostream>
#include <math.h>

using namespace std;

int main()
{
	double liczba = 0;
	double wynik = 0;
	while (cin >> liczba)
	{
		wynik = 20*(log10(liczba));
		cout << "************" << endl;
		cout << wynik << endl;
		cout << "************" << endl;
	}
	return 0;
}