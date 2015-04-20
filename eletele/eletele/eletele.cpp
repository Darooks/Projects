#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define ILOSC_SLOW 2049

bool czy_iso(ifstream& myFile, string plik [])			//nie mozna kopiowac obiektu fstream dlatego trzeba odniesc sie do referencji (&)
{
	string iso[18] = { "0xA1", "0xC6", "0xCA", "0xA3", "0xD1", "0xD3", "0xA6", "0xAC", "0xAF", "0xB1", "0xE6", "0xEA", "0xB3", "0xF1", "0xF3", "0xB6", "0xBC", "0xBF" };

	for (int i = 0; i < ILOSC_SLOW; i++)
	{
		if (plik[i] == "")
			break;
		for (int j = 0; j < 18; j++)
		{
			if ((plik[i] == iso[j]))
				break;
			if (plik[i] != iso[j] && j == 17)
				return false;
		}
	}
	
	return true;
}

bool czy_win(ifstream& myFile, string plik[])			//nie mozna kopiowac obiektu fstream dlatego trzeba odniesc sie do referencji (&)
{
	string Win1250[18] = { "0xA5", "0xC6", "0xCA", "0xA3", "0xD1", "0xD3", "0x8C", "0x8F", "0xAF", "0xB9", "0xE6", "0xEA", "0xB3", "0xF1", "0xF3", "0x9C", "0x9F", "0xBF" };
	

	for (int i = 0; i < ILOSC_SLOW; i++)
	{
		if (plik[i] == "")
			break;
		for (int j = 0; j < 18; j++)
		{
			if ((plik[i] == Win1250[j]))
				break;
			if (plik[i] != Win1250[j] && j == 17)
				return false;
		}
	}

	return true;
}

bool czy_CP(ifstream& myFile, string plik[])			//nie mozna kopiowac obiektu fstream dlatego trzeba odniesc sie do referencji (&)
{
	string CP852[18] = { "0xA4", "0x8F", "0xA8", "0x9D", "0xE3", "0xE0", "0x97", "0x8D", "0xBD", "0xA5", "0x86", "0xA9", "0x88", "0xE4", "0xA2", "0x98", "0xAB", "0xBE" };
	

	for (int i = 0; i < ILOSC_SLOW; i++)
	{
		if (plik[i] == "")
			break;
		for (int j = 0; j < 18; j++)
		{
			if ((plik[i] == CP852[j]))
				break;
			if (plik[i] != CP852[j] && j == 17)
				return false;
		}
	}

	return true;
}

bool czy_mazovia(ifstream& myFile, string plik[])			//nie mozna kopiowac obiektu fstream dlatego trzeba odniesc sie do referencji (&)
{
	string Mazovia[18] = { "0x8F", "0x95", "0x90", "0x9C", "0xA5", "0xA3", "0x98", "0xA0", "0xA1", "0x86", "0x8D", "0x91", "0x92", "0xA4", "0xA2", "0x9E", "0xA6", "0xA7" };

	for (int i = 0; i < ILOSC_SLOW; i++)
	{
		if (plik[i] == "")
			break;
		for (int j = 0; j < 18; j++)
		{
			if ((plik[i] == Mazovia[j]))
				break;
			if (plik[i] != Mazovia[j] && j == 17)
				return false;
		}
	}

	return true;
}

bool czy_utf(ifstream& myFile, string plik[])			//nie mozna kopiowac obiektu fstream dlatego trzeba odniesc sie do referencji (&)
{
	string UTF8[36] = { "0xC4", "0x84", "0xC4", "0x86", "0xC4", "0x98", "0xC5", "0x81", "0xC5", "0x83", "0xC3", "0x93", "0xC5", "0x9A", "0xC5", "0xB9", "0xC5", "0xBB", "0xC4", "0x85", "0xC4", "0x87", "0xC4", "0x99", "0xC5", "0x82", "0xC5", "0x84", "0xC3", "0xB3", "0xC5", "0x9B", "0xC5", "0xBA", "0xC5", "0xBC" };

	for (int i = 0; i < ILOSC_SLOW; i++)
	{
		if (plik[i] == "")
			break;
		for (int j = 0; j < 36; j++)
		{
			if ((plik[i] == UTF8[j]))
				break;
			if (plik[i] != UTF8[j] && j == 35)
				return false;
		}
	}

	return true;
}

void z_iso(string jaki_kod, string plik[], ofstream& newFile)
{
	string UTF8[36] = { "0xC4", "0x84", "0xC4", "0x86", "0xC4", "0x98", "0xC5", "0x81", "0xC5", "0x83", "0xC3", "0x93", "0xC5", "0x9A", "0xC5", "0xB9", "0xC5", "0xBB", "0xC4", "0x85", "0xC4", "0x87", "0xC4", "0x99", "0xC5", "0x82", "0xC5", "0x84", "0xC3", "0xB3", "0xC5", "0x9B", "0xC5", "0xBA", "0xC5", "0xBC" };
	string Mazovia[18] = { "0x8F", "0x95", "0x90", "0x9C", "0xA5", "0xA3", "0x98", "0xA0", "0xA1", "0x86", "0x8D", "0x91", "0x92", "0xA4", "0xA2", "0x9E", "0xA6", "0xA7" };
	string CP852[18] = { "0xA4", "0x8F", "0xA8", "0x9D", "0xE3", "0xE0", "0x97", "0x8D", "0xBD", "0xA5", "0x86", "0xA9", "0x88", "0xE4", "0xA2", "0x98", "0xAB", "0xBE" };
	string Win1250[18] = { "0xA5", "0xC6", "0xCA", "0xA3", "0xD1", "0xD3", "0x8C", "0x8F", "0xAF", "0xB9", "0xE6", "0xEA", "0xB3", "0xF1", "0xF3", "0x9C", "0x9F", "0xBF" };
	string iso[18] = { "0xA1", "0xC6", "0xCA", "0xA3", "0xD1", "0xD3", "0xA6", "0xAC", "0xAF", "0xB1", "0xE6", "0xEA", "0xB3", "0xF1", "0xF3", "0xB6", "0xBC", "0xBF" };
	int index_utf;
	for (int i = 0; i < ILOSC_SLOW; i++)
	{
		if (plik[i] == "")
			break;
		if (jaki_kod == "Mazovia")
		{
			for (int j = 0; j < 18; j++)
			{
				if (plik[i] == iso[j])
				{
					newFile << Mazovia[j];
					newFile << " ";
					break;
				}
			}
		}
		else if (jaki_kod == "CP")
		{
			for (int j = 0; j < 18; j++)
			{
				if (plik[i] == iso[j])
				{
					newFile << CP852[j];
					newFile << " ";
					break;
				}
			}
		}
		else if (jaki_kod == "WIN")
		{
			for (int j = 0; j < 18; j++)
			{
				if (plik[i] == iso[j])
				{
					newFile << Win1250[j];
					newFile << " ";
					break;
				}
			}
		}
		else if (jaki_kod == "UTF")
		{
			for (int j = 0; j < 18; j++)
			{
				if (plik[i] == iso[j])
				{
					index_utf = 2 * j;
					newFile << UTF8[index_utf];
					newFile << " ";
					newFile << UTF8[index_utf + 1];
					newFile << " ";

					break;
				}
			}
		}

	}
}

void z_mazovia(string jaki_kod, string plik[], ofstream& newFile)
{
	string UTF8[36] = { "0xC4", "0x84", "0xC4", "0x86", "0xC4", "0x98", "0xC5", "0x81", "0xC5", "0x83", "0xC3", "0x93", "0xC5", "0x9A", "0xC5", "0xB9", "0xC5", "0xBB", "0xC4", "0x85", "0xC4", "0x87", "0xC4", "0x99", "0xC5", "0x82", "0xC5", "0x84", "0xC3", "0xB3", "0xC5", "0x9B", "0xC5", "0xBA", "0xC5", "0xBC" };
	string Mazovia[18] = { "0x8F", "0x95", "0x90", "0x9C", "0xA5", "0xA3", "0x98", "0xA0", "0xA1", "0x86", "0x8D", "0x91", "0x92", "0xA4", "0xA2", "0x9E", "0xA6", "0xA7" };
	string CP852[18] = { "0xA4", "0x8F", "0xA8", "0x9D", "0xE3", "0xE0", "0x97", "0x8D", "0xBD", "0xA5", "0x86", "0xA9", "0x88", "0xE4", "0xA2", "0x98", "0xAB", "0xBE" };
	string Win1250[18] = { "0xA5", "0xC6", "0xCA", "0xA3", "0xD1", "0xD3", "0x8C", "0x8F", "0xAF", "0xB9", "0xE6", "0xEA", "0xB3", "0xF1", "0xF3", "0x9C", "0x9F", "0xBF" };
	string iso[18] = { "0xA1", "0xC6", "0xCA", "0xA3", "0xD1", "0xD3", "0xA6", "0xAC", "0xAF", "0xB1", "0xE6", "0xEA", "0xB3", "0xF1", "0xF3", "0xB6", "0xBC", "0xBF" };
	int index_utf;
	for (int i = 0; i < ILOSC_SLOW; i++)
	{
		if (plik[i] == "")
			break;
		if (jaki_kod == "ISO")
		{
			for (int j = 0; j < 18; j++)
			{
				if (plik[i] == Mazovia[j])
				{
					newFile << iso[j];
					newFile << " ";
					break;
				}
			}
		}
		else if (jaki_kod == "CP")
		{
			for (int j = 0; j < 18; j++)
			{
				if (plik[i] == Mazovia[j])
				{
					newFile << CP852[j];
					newFile << " ";
					break;
				}
			}
		}
		else if (jaki_kod == "WIN")
		{
			for (int j = 0; j < 18; j++)
			{
				if (plik[i] == Mazovia[j])
				{
					newFile << Win1250[j];
					newFile << " ";
					break;
				}
			}
		}
		else if (jaki_kod == "UTF")
		{
			for (int j = 0; j < 18; j++)
			{
				if (plik[i] == Mazovia[j])
				{
					index_utf = 2 * j;
					newFile << UTF8[index_utf];
					newFile << " ";
					newFile << UTF8[index_utf + 1];
					newFile << " ";

					break;
				}
			}
		}

	}
}

void z_cp(string jaki_kod, string plik[], ofstream& newFile)
{
	string UTF8[36] = { "0xC4", "0x84", "0xC4", "0x86", "0xC4", "0x98", "0xC5", "0x81", "0xC5", "0x83", "0xC3", "0x93", "0xC5", "0x9A", "0xC5", "0xB9", "0xC5", "0xBB", "0xC4", "0x85", "0xC4", "0x87", "0xC4", "0x99", "0xC5", "0x82", "0xC5", "0x84", "0xC3", "0xB3", "0xC5", "0x9B", "0xC5", "0xBA", "0xC5", "0xBC" };
	string Mazovia[18] = { "0x8F", "0x95", "0x90", "0x9C", "0xA5", "0xA3", "0x98", "0xA0", "0xA1", "0x86", "0x8D", "0x91", "0x92", "0xA4", "0xA2", "0x9E", "0xA6", "0xA7" };
	string CP852[18] = { "0xA4", "0x8F", "0xA8", "0x9D", "0xE3", "0xE0", "0x97", "0x8D", "0xBD", "0xA5", "0x86", "0xA9", "0x88", "0xE4", "0xA2", "0x98", "0xAB", "0xBE" };
	string Win1250[18] = { "0xA5", "0xC6", "0xCA", "0xA3", "0xD1", "0xD3", "0x8C", "0x8F", "0xAF", "0xB9", "0xE6", "0xEA", "0xB3", "0xF1", "0xF3", "0x9C", "0x9F", "0xBF" };
	string iso[18] = { "0xA1", "0xC6", "0xCA", "0xA3", "0xD1", "0xD3", "0xA6", "0xAC", "0xAF", "0xB1", "0xE6", "0xEA", "0xB3", "0xF1", "0xF3", "0xB6", "0xBC", "0xBF" };
	int index_utf;
	for (int i = 0; i < ILOSC_SLOW; i++)
	{
		if (plik[i] == "")
			break;
		if (jaki_kod == "ISO")
		{
			for (int j = 0; j < 18; j++)
			{
				if (plik[i] == CP852[j])
				{
					newFile << iso[j];
					newFile << " ";
					break;
				}
			}
		}
		else if (jaki_kod == "Mazovia")
		{
			for (int j = 0; j < 18; j++)
			{
				if (plik[i] == CP852[j])
				{
					newFile << Mazovia[j];
					newFile << " ";
					break;
				}
			}
		}
		else if (jaki_kod == "WIN")
		{
			for (int j = 0; j < 18; j++)
			{
				if (plik[i] == CP852[j])
				{
					newFile << Win1250[j];
					newFile << " ";
					break;
				}
			}
		}
		else if (jaki_kod == "UTF")
		{
			for (int j = 0; j < 18; j++)
			{
				if (plik[i] == CP852[j])
				{
					index_utf = 2 * j;
					newFile << UTF8[index_utf];
					newFile << " ";
					newFile << UTF8[index_utf + 1];
					newFile << " ";

					break;
				}
			}
		}

	}
}

void z_win(string jaki_kod, string plik[], ofstream& newFile)
{
	string UTF8[36] = { "0xC4", "0x84", "0xC4", "0x86", "0xC4", "0x98", "0xC5", "0x81", "0xC5", "0x83", "0xC3", "0x93", "0xC5", "0x9A", "0xC5", "0xB9", "0xC5", "0xBB", "0xC4", "0x85", "0xC4", "0x87", "0xC4", "0x99", "0xC5", "0x82", "0xC5", "0x84", "0xC3", "0xB3", "0xC5", "0x9B", "0xC5", "0xBA", "0xC5", "0xBC" };
	string Mazovia[18] = { "0x8F", "0x95", "0x90", "0x9C", "0xA5", "0xA3", "0x98", "0xA0", "0xA1", "0x86", "0x8D", "0x91", "0x92", "0xA4", "0xA2", "0x9E", "0xA6", "0xA7" };
	string CP852[18] = { "0xA4", "0x8F", "0xA8", "0x9D", "0xE3", "0xE0", "0x97", "0x8D", "0xBD", "0xA5", "0x86", "0xA9", "0x88", "0xE4", "0xA2", "0x98", "0xAB", "0xBE" };
	string Win1250[18] = { "0xA5", "0xC6", "0xCA", "0xA3", "0xD1", "0xD3", "0x8C", "0x8F", "0xAF", "0xB9", "0xE6", "0xEA", "0xB3", "0xF1", "0xF3", "0x9C", "0x9F", "0xBF" };
	string iso[18] = { "0xA1", "0xC6", "0xCA", "0xA3", "0xD1", "0xD3", "0xA6", "0xAC", "0xAF", "0xB1", "0xE6", "0xEA", "0xB3", "0xF1", "0xF3", "0xB6", "0xBC", "0xBF" };
	int index_utf;
	for (int i = 0; i < ILOSC_SLOW; i++)
	{
		if (plik[i] == "")
			break;
		if (jaki_kod == "ISO")
		{
			for (int j = 0; j < 18; j++)
			{
				if (plik[i] == Win1250[j])
				{
					newFile << iso[j];
					newFile << " ";
					break;
				}
			}
		}
		else if (jaki_kod == "Mazovia")
		{
			for (int j = 0; j < 18; j++)
			{
				if (plik[i] == Win1250[j])
				{
					newFile << Mazovia[j];
					newFile << " ";
					break;
				}
			}
		}
		else if (jaki_kod == "CP")
		{
			for (int j = 0; j < 18; j++)
			{
				if (plik[i] == Win1250[j])
				{
					newFile << CP852[j];
					newFile << " ";
					break;
				}
			}
		}
		else if (jaki_kod == "UTF")
		{
			for (int j = 0; j < 18; j++)
			{
				if (plik[i] == Win1250[j])
				{
					index_utf = 2 * j;
					newFile << UTF8[index_utf];
					newFile << " ";
					newFile << UTF8[index_utf + 1];
					newFile << " ";

					break;
				}
			}
		}

	}
}

void z_UTF(string jaki_kod, string plik[], ofstream& newFile)
{
	string UTF8[36] = { "0xC4", "0x84", "0xC4", "0x86", "0xC4", "0x98", "0xC5", "0x81", "0xC5", "0x83", "0xC3", "0x93", "0xC5", "0x9A", "0xC5", "0xB9", "0xC5", "0xBB", "0xC4", "0x85", "0xC4", "0x87", "0xC4", "0x99", "0xC5", "0x82", "0xC5", "0x84", "0xC3", "0xB3", "0xC5", "0x9B", "0xC5", "0xBA", "0xC5", "0xBC" };
	string Mazovia[18] = { "0x8F", "0x95", "0x90", "0x9C", "0xA5", "0xA3", "0x98", "0xA0", "0xA1", "0x86", "0x8D", "0x91", "0x92", "0xA4", "0xA2", "0x9E", "0xA6", "0xA7" };
	string CP852[18] = { "0xA4", "0x8F", "0xA8", "0x9D", "0xE3", "0xE0", "0x97", "0x8D", "0xBD", "0xA5", "0x86", "0xA9", "0x88", "0xE4", "0xA2", "0x98", "0xAB", "0xBE" };
	string Win1250[18] = { "0xA5", "0xC6", "0xCA", "0xA3", "0xD1", "0xD3", "0x8C", "0x8F", "0xAF", "0xB9", "0xE6", "0xEA", "0xB3", "0xF1", "0xF3", "0x9C", "0x9F", "0xBF" };
	string iso[18] = { "0xA1", "0xC6", "0xCA", "0xA3", "0xD1", "0xD3", "0xA6", "0xAC", "0xAF", "0xB1", "0xE6", "0xEA", "0xB3", "0xF1", "0xF3", "0xB6", "0xBC", "0xBF" };
	int index_utf;
	for (int i = 0; i < ILOSC_SLOW; i++)
	{
		if (plik[i] == "")
			break;
		
		if (jaki_kod == "ISO")
		{
			for (int j = 1; j < 36; j += 2)
			{
				if (plik[i] == UTF8[j])
				{
					index_utf = j / 2;
					newFile << iso[index_utf];
					newFile << " ";
					break;
				}
			}
		}
		else if (jaki_kod == "Mazovia")
		{
			for (int j = 1; j < 36; j += 2)
			{
				if (plik[i] == UTF8[j])
				{
					index_utf = j / 2;
					newFile << Mazovia[index_utf];
					newFile << " ";
					break;
				}
			}
		}
		else if (jaki_kod == "CP")
		{
			for (int j = 1; j < 36; j += 2)
			{
				if (plik[i] == UTF8[j])
				{
					index_utf = j / 2;
					newFile << CP852[index_utf];
					newFile << " ";
					break;
				}
			}
		}
		else if (jaki_kod == "WIN")
		{
			for (int j = 1; j < 36; j += 2)
			{
				if (plik[i] == UTF8[j])
				{
					index_utf = j / 2;
					newFile << Win1250[index_utf];
					newFile << " ";
					break;
				}
			}
		}
		

	}
}

void nowy_plik(string plik[], string jaki_kod)
{
	string nazwa;
	
	string kodowanie;

	cout << "Podaj nazwe nowego pliku:" << endl;
	getline(cin, nazwa);
	ofstream newFile(nazwa, ios::binary | ios::app);

	cout << "Wybierz kodowanie:" << endl;
	cout << "1. ISO" << endl;
	cout << "2. WIN" << endl;
	cout << "3. CP" << endl;
	cout << "4. Mazovia" << endl;
	cout << "5. UTF" << endl;

	getline(cin, kodowanie);

	if (jaki_kod == "iso")
		z_iso(kodowanie, plik, newFile);
	else if (jaki_kod == "win")
		z_win(kodowanie, plik, newFile);
	else if (jaki_kod == "mazovia")
		z_mazovia(kodowanie, plik, newFile);
	else if (jaki_kod == "cp")
		z_cp(kodowanie, plik, newFile);
	else if (jaki_kod == "utf")
		z_UTF(kodowanie, plik, newFile);

	newFile.close();

}

void rozpoznanie(ifstream& myFile)
{
	bool to_jest_iso = false;
	bool to_jest_win = false;
	bool to_jest_CP = false;
	bool to_jest_mazovia = false;
	bool to_jest_utf = false;
	int size = 0;
	string plik[ILOSC_SLOW];
	string jaki_kod = "";

	for (int i = 0; i < ILOSC_SLOW; i++)
		plik[i] = "";

	for (int i = 0; i < ILOSC_SLOW; i++)
	{
		if (myFile.eof() || size >= 4096)
			break;

		myFile >> plik[i];
		size = myFile.tellg();
		
	}

	
	to_jest_iso = czy_iso(myFile, plik);
	to_jest_win = czy_win(myFile, plik);
	to_jest_CP = czy_CP(myFile, plik);
	to_jest_mazovia = czy_mazovia(myFile, plik);
	to_jest_utf = czy_utf(myFile, plik);

	if (to_jest_iso)
	{
		cout << "Plik zakodowany w ISO " << endl;
		jaki_kod = "iso";
	}
	if (to_jest_win)
	{
		cout << "Plik zakodowany w Win1250 " << endl;
		jaki_kod = "win";
	}
	if (to_jest_CP)
	{
		cout << "Plik zakodowany w CP852 " << endl;
		jaki_kod = "cp";
	}
	if (to_jest_mazovia)
	{
		cout << "Plik zakodowany w Mazovia " << endl;
		jaki_kod = "mazovia";
	}
	if (to_jest_utf)
	{
		cout << "Plik zakodowany w UTF" << endl;
		jaki_kod = "utf";
	}
	nowy_plik(plik, jaki_kod);
}



int main()
{
	string nazwa;
	while (true)
	{
		cout << "Jaki plik chcialbys otworzyc?" << endl;

		getline(cin, nazwa);

		ifstream myFile(nazwa + ".txt", ios::binary);

		rozpoznanie(myFile);

		myFile.close();
	}


	system("pause");
	return 0;
}