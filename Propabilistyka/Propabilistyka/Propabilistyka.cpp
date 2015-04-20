#include <iostream>
using namespace std;

//struct dane
//{
//	int ID;
//	//string nazwa;
//};

struct wezel
{
	int ID = 0;
	wezel *pierwsze_dziecko = NULL, *rodzic = NULL, *rodzenstwo = NULL;
};

void stworz_rodzenstwo(wezel*& pierwsze, wezel* rodzic, int n)
{
	for (int k = 1; k <= n; k++)
	{
		wezel* brat = new wezel;
		brat->ID = k;
		brat->rodzic = rodzic;
		pierwsze->rodzenstwo = brat;
		//stworz_dzieci(brat, n);
		brat = pierwsze;
		
	}
}

void create(wezel*& pierwsze_dziecko, int n)
{
		for (int i = 1; i <= n; i++)
		{
			wezel* dziecko;
			dziecko = new wezel;

			dziecko->ID = i;
			dziecko->rodzic = pierwsze_dziecko;
			pierwsze_dziecko->pierwsze_dziecko = dziecko;
			//stworz_rodzenstwo(dziecko, pierwsze_dziecko, n);

			dziecko = pierwsze_dziecko;

		}
}

void show(wezel* korzen, int n)
{
	korzen = korzen->pierwsze_dziecko;
	wezel *pierwszy_brat = new wezel;

	for (int i = 1; i <= n - 2; i++)
	{
		pierwszy_brat = korzen;
		for (int j = 1; j <= n; j++)
		{
			if (korzen == NULL)
				break;
			cout << korzen->ID << " ";
			korzen = korzen->rodzenstwo;
		}
		korzen = pierwszy_brat;
		korzen = korzen->pierwsze_dziecko;
		cout << endl;
	}
}

int main()
{
	int n;
	cout << "Podaj ilosc elementow permutacji: " << endl;
	cin >> n;

	wezel* korzen;
	korzen = new wezel;

	create(korzen, n);
	show(korzen, n);


	system("pause");
	return 0;
}