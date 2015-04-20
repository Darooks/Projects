#include <iostream>
#include <fstream>
using namespace std;

#define ILOSC_LITER 20
#define POCZATEK_MALYCH_LITER 97
#define KONIEC_MALYCH_LITER 122
#define ILOSC_ALFABETU 26
#define MYSLNIK '-'
#define TRZYKROPEK '#'
#define BRAK '%'
#define PRZESUNIECIE_TRZECH_KROPEK 3
#define PRZESUNIECIE_INTERPUNKCYJNE 1
#define POCZATEK_DUZYCH_LITER 65 //<-- KOD ASCII
#define KONIEC_DUZYCH_LITER 90  //<-- KOD ASCII

struct Trie
{
	char nazwa[20];
	char tlumaczenie[20];

	Trie *wskaznik[26];
	Trie() {
		for (int i = 0; i < ILOSC_ALFABETU; i++)
		{
			wskaznik[i] = NULL;
		}
		nazwa[0] = NULL;
		tlumaczenie[0] = NULL;
	}
};

struct do_wypisania
{
	char fraza[ILOSC_LITER];

	do_wypisania *next;

	do_wypisania()
	{
		next = NULL;
		fraza[0] = NULL;
	}
};

struct lista_slow
{
	do_wypisania *last;
	do_wypisania *first;
	lista_slow()
	{
		last = NULL;
		first = NULL;
	}
};


char czy_interpunkcja(char slowo[]) // ! ? , . ... ; : -
{
	int licznik = strlen(slowo);

	switch (slowo[licznik - 1])
	{
	case '.':
		//cout << slowo[licznik - 3] << slowo[licznik - 1] << slowo[licznik - 2] << endl;
		if (slowo[licznik - 3] == '.' && slowo[licznik - 2] == '.' && slowo[licznik - 1] == '.')
		{
			return TRZYKROPEK;
		}
		else
			return '.';
		return '.';
	case ',':
		return ',';
	case ';':
		return ';';
	case ':':
		return ':';
	case '!':
		return '!';
	case '?':
		return '?';
	default:
		return BRAK;
	}
	return BRAK;
}

void dodaj_do_slownika(Trie *slownik, char slowo[])
{
	int index;
	static int licznik = 0;
	char tlumaczenie_cin[ILOSC_LITER];
	bool skoncz_wczytywanie = false;

	for (int i = 0; i < ILOSC_LITER; i++)
	{

		if (skoncz_wczytywanie)
			break;
		if (slowo[i] == NULL)
		{
			cin >> tlumaczenie_cin;
			//Trie *child = new Trie;

			//child->nazwa[0] = slowo[i];
			//for (int i = 0; i < ILOSC_ALFABETU; i++)
			//{
				//child->wskaznik[i] = NULL;
			//}

			//cin >> tlumaczenie_cin;
			//slownik = slownik->wskaznik[]
			strcpy(slownik->tlumaczenie, tlumaczenie_cin);
			skoncz_wczytywanie = true;
		}
		if (skoncz_wczytywanie)
			break;
		index = (int)slowo[i] - 97;
		if (slownik != NULL)
		{
			
			if (slownik->wskaznik[index] == NULL) // jesli nie ma dziecka
			{
				Trie *child = new Trie;

				child->nazwa[0] = slowo[i];
				for (int i = 0; i < ILOSC_ALFABETU; i++)
				{
					child->wskaznik[i] = NULL;
				}
				if (slowo[i + 1] == NULL || slowo[i] == NULL)
				{
					cin >> tlumaczenie_cin;
					for (int j = 0; j < ILOSC_LITER; j++)
					{
						if (tlumaczenie_cin[j] == NULL)
						{
							child->tlumaczenie[j] = NULL;
							skoncz_wczytywanie = true;
							break;
						}
						child->tlumaczenie[j] = tlumaczenie_cin[j];
					}
				}
				slownik->wskaznik[index] = child;
				slownik = slownik->wskaznik[index];
			}
			else
			{
				slownik = slownik->wskaznik[index];
				//Trie *child = new Trie;
			}
		}
	}
}

char zamien_na_mala(char litera)
{
	int pomocnicze = (int)litera + 32;
	litera = (char)pomocnicze;
	return litera;
}

char zamien_na_duza(char litera)
{
	int pomocnicze = (int)litera - 32;
	litera = (char)pomocnicze;
	return litera;
}

void brak_tlumaczenia(Trie *slownik, char slowo[])
{
	int usuwam_interpunkcje;
	char czy_istnieje_znak = czy_interpunkcja(slowo);
	if (slowo[0] == MYSLNIK)
	{
		return;
	}
	if (slowo[0] >= POCZATEK_DUZYCH_LITER && slowo[0] <= KONIEC_DUZYCH_LITER)
	{
		slowo[0] = zamien_na_mala(slowo[0]);
	}

	if (czy_istnieje_znak != BRAK)
	{
		if (czy_istnieje_znak == TRZYKROPEK)
		{
			usuwam_interpunkcje = strlen(slowo) - PRZESUNIECIE_TRZECH_KROPEK;
			slowo[usuwam_interpunkcje] = NULL;
		}
		else
		{
			usuwam_interpunkcje = strlen(slowo) - PRZESUNIECIE_INTERPUNKCYJNE;
			slowo[usuwam_interpunkcje] = NULL;
		}
	}

	for (int i = 0; i < ILOSC_LITER; i++)
	{
		if (slowo[i] == NULL)
			break;

		int index = (int)slowo[i] - 97;
		if (slownik->wskaznik[index] == NULL)
		{
			//fstream cout;
			//cout.open("out.txt", ios::app); fstream plik;
			//plik << slowo << " ";
			cout << slowo << " ";
			return;
		}
		else
		{
			slownik = slownik->wskaznik[index];
		}
	}
}

bool tlumacz_do_listy(Trie *slownik, char slowo[], lista_slow *lista)
{
	bool czy_duza = false;
	int index;
	char czy_istnieje_znak = czy_interpunkcja(slowo);
	int usuwam_interpunkcje;

	if (czy_istnieje_znak != BRAK)
	{
		if (czy_istnieje_znak == TRZYKROPEK)
		{
			usuwam_interpunkcje = strlen(slowo) - PRZESUNIECIE_TRZECH_KROPEK;
			slowo[usuwam_interpunkcje] = NULL;
		}
		else
		{
			usuwam_interpunkcje = strlen(slowo) - PRZESUNIECIE_INTERPUNKCYJNE;
			slowo[usuwam_interpunkcje] = NULL;
		}
	}

	if (slowo[0] != MYSLNIK)
	{
		if (slowo[0] >= POCZATEK_MALYCH_LITER && slowo[0] <= KONIEC_MALYCH_LITER)
		{
			czy_duza = false;
		}
		else
		{
			slowo[0] = zamien_na_mala(slowo[0]);
			czy_duza = true;
		}

		for (int i = 0; i < ILOSC_LITER; i++)
		{
			index = (int)slowo[i] - 97;

			if (slownik->wskaznik[index] == NULL)
			{
				//fstream cout;
				//cout.open("out.txt", ios::app); fstream plik;
				cout << "Brak slow: " << slowo << " ";
				//plik << "Brak slow: " << slowo << " ";
				return false;
			}
			else
			{
				slownik = slownik->wskaznik[index];
			}
			
			if (slowo[i + 1] == NULL || slowo[i] == NULL)
			{
				do_wypisania *nowy = new do_wypisania;
				nowy->next = NULL;

				if (czy_duza == true)
				{
					nowy->fraza[0] = zamien_na_duza(slownik->tlumaczenie[0]);
					czy_duza = false;
				}
				else
					nowy->fraza[0] = slownik->tlumaczenie[0];

				for (int j = 1; j < ILOSC_LITER; j++)
				{
					if (slownik->tlumaczenie[j] == NULL)
					{
						if (czy_istnieje_znak != BRAK)
						{
							if (czy_istnieje_znak == TRZYKROPEK)
							{
								for (int przesuwam_index = 0; przesuwam_index < PRZESUNIECIE_TRZECH_KROPEK; przesuwam_index++)
								{
									nowy->fraza[j + przesuwam_index] = '.';
								}
								nowy->fraza[j + PRZESUNIECIE_TRZECH_KROPEK] = NULL;
								break;
							}
							else
							{
								nowy->fraza[j] = czy_istnieje_znak;
								nowy->fraza[j + PRZESUNIECIE_INTERPUNKCYJNE] = NULL;
								break;
							}
						}
						else
						{
							nowy->fraza[j] = NULL;
							break;
						}
					}
					nowy->fraza[j] = slownik->tlumaczenie[j];
				}
				if (lista->first == NULL)
				{
					lista->first = nowy;
					lista->last = nowy;
				}
				else
				{
					lista->last->next = nowy;
					lista->last = nowy;
				}
				break;
			}
		}
	}
	else
	{
		do_wypisania *nowy = new do_wypisania;
		nowy->next = NULL;

		if (lista->first == NULL)
		{
			lista->first = nowy;
			lista->last = nowy;
		}
		else
		{
			lista->last->next = nowy;
			lista->last = nowy;
		}
		//while (lista->next !=         NULL)
		//{
		//      lista = lista->next;
		//}
		nowy->fraza[0] = MYSLNIK;
		nowy->fraza[1] = NULL;
	}
	return true;
}

void wypisz(lista_slow *lista)
{
	//fstream cout;
	//cout.open("out.txt", ios::app);fstream plik;

	do_wypisania *temp = lista->first;
	while (true)
	{
		cout << temp->fraza << " ";
		//plik << temp->fraza << " ";
		if (temp == lista->last)
			break;
		temp = temp->next;
	}
	cout << endl;

}

int main()
{
	//std::ifstream in("30.in");
	//std::streambuf *cinbuf = std::cin.rdbuf();
	//std::cin.rdbuf(in.rdbuf());

	//fstream cout;
	//cout.open("out.txt", ios::app); fstream plik;

	Trie *slownik = new Trie;
	// do_wypisania *lista = new do_wypisania;
	lista_slow *lista = new lista_slow;
	char slowo[20];
	char czy_wypisywac = true;
	bool czy_wyswietlilem_wczesniej = false;
	bool czy_jest_w_slowniku = true;
	while (cin >> slowo)
	{
		if (slowo[0] >= POCZATEK_MALYCH_LITER && slowo[0] <= KONIEC_MALYCH_LITER)
		{
			dodaj_do_slownika(slownik, slowo);
		}

		else
		{
			czy_jest_w_slowniku = tlumacz_do_listy(slownik, slowo, lista);

			if (cin.get() == ' ' && cin.peek() == '\n')
			{
				if (czy_jest_w_slowniku)
				{
					wypisz(lista);
					delete lista;
					lista_slow *lista = new lista_slow;
				}
				else
				{
					brak_tlumaczenia(slownik, slowo);
					delete lista;
					lista_slow *lista = new lista_slow;
					cout << endl;
					czy_jest_w_slowniku = true;
				}
			}

			else
			{
				while (cin >> slowo)
				{
					if (czy_jest_w_slowniku)
					{
						czy_jest_w_slowniku = tlumacz_do_listy(slownik, slowo, lista);
					}
					else
						brak_tlumaczenia(slownik, slowo);

					if (cin.get() == ' ' && cin.peek() == '\n')
					{
						if (czy_jest_w_slowniku)
						{
							wypisz(lista);
							delete lista;
							lista_slow *lista = new lista_slow;
							break;
						}
						else
						{
							cout << endl;
							czy_jest_w_slowniku = true;
							delete lista;
							lista_slow *lista = new lista_slow;
							break;
						}
					}
				}
			}
		}
	}
	//plik << endl;
	//plik.close();
	return 0;
}
