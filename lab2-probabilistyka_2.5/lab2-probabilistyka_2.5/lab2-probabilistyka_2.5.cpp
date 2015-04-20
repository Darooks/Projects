#include <iostream>
using namespace std;

int main()
{
	int b = 10;
	int ib = b - 1;
	int licznik = 1;

	for (int i = ib; i = 0; i--)
	{
		b = b ^ i;
		cout << "x" << licznik << " = " << b << endl;
	}

	system("pause");
	return 0;
}