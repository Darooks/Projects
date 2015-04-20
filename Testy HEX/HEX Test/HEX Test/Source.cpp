#include <iostream>
#include <fstream>
using namespace std;

#define NUMER_LINII		33

int main()
{
	int kolejna_linia = 0, znaleziona_komenda = 0;
	char linijka[65];
	ifstream in("wejscie.txt");
	streambuf *cinbuf = std::cin.rdbuf();
	cin.rdbuf(in.rdbuf());
	while(cin.getline(linijka, 65))
	{
		kolejna_linia += 1;
		if(isalpha(linijka[0]))
		{
			znaleziona_komenda += 1;
			if (znaleziona_komenda == ((NUMER_LINII / 2) + 1))
			{
				break;
			}
		}
	}
	cout << "# Linia testu : " << kolejna_linia << endl;
	system("pause");
	return 0;
}