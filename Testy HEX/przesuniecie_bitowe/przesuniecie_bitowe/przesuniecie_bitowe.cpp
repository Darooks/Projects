#include <iostream>

using namespace std;

#define PRZESUN 3
#define ILE 122

int main()
{
	int index = 0;
	int a = ILE;
	int b = ILE;
	int c = ILE;
	int d = ILE;
	char tab[16] = { "ab" };

	//index = (a << PRZESUN) + (b << PRZESUN) + (c << PRZESUN) + (d << PRZESUN) + (b << PRZESUN) + (c << PRZESUN) + (d << PRZESUN) + (b << PRZESUN) + (c << PRZESUN) + (d << PRZESUN) + (b << PRZESUN) + (c << PRZESUN) + (d << PRZESUN) + (b << PRZESUN) + (c << PRZESUN);

	//cout << index << endl;
	//cout << (97 << 15)%40000 << endl;

	for (int i = 0; i < 15; i++)
	{
		if (tab[i] == NULL)
			break;
		index += ((int)tab[i] << i);
	}
	cout << index % 40000 << endl;

	system("pause");
	return 0;
}