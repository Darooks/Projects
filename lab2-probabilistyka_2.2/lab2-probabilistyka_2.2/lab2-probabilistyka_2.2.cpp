#include <iostream>
using namespace std;

int main()
{
	//Generator od 0 do 11, jesli chcesz zmian to zmien x_max
	int x_max, x_0, a, c, m;
	x_max = 11;
	x_0 = x_max;
	a = 13;
	c = 7;
	m = 12;
	int licznik = 1;

	x_0 = ((a * x_0) + c) % m;
	cout << "x" << licznik << " = " << x_0 << endl;
	licznik++;

	while (x_0 != x_max)
	{
		x_0 = ((a * x_0) + c) % m;
		cout << "x" << licznik << " = " << x_0 << endl;
		licznik++;
	}

	system("pause");
	return 0;
}