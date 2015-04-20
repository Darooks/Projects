#include <iostream>
using namespace std;

int main()
{
	int liczba = 2;
	int tab[] = { 1, 2, 3, 4, 5 };
	int *wsk = tab;
	*wsk = *(wsk + 1);
	int c = *wsk + tab[4];
	cout << *(wsk) << endl;
	cout << c << endl;

	system("pause");
	return 0;
}