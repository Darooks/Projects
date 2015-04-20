#include <iostream>

using namespace std;

bool czyPierwsza(int liczba)
{
	if (liczba == 1)
	{
		return false;
	}

	for (int i = 2; i < liczba; i++)
	{
		if (liczba % i == 0)
		{
			return false;
		}
	}
	return true;
}

int main()
{
	int liczba;

	//while (true)
	//{
		cin >> liczba;

		if (czyPierwsza(liczba) == true)
		{
			cout << "TAK" << endl;
		}
		else
			cout << "NIE" << endl;
	//}

	return 0;
}