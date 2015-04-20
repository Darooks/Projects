#include <iostream>
#include <fstream>

using namespace std;

#define ROZMIAR 40000
#define POCZATEK_DUZYCH_LITER 65 //<-- KOD ASCII
#define KONIEC_DUZYCH_LITER 90  //<-- KOD ASCII
#define POCZATEK_MALYCH_LITER 97
#define KONIEC_MALYCH_LITER 122
#define ILOSC_LITER 20
#define NIE_MA_SLOWA_W_SLOWNIKU 0
#define MYSLNIK '-'
#define TRZYKROPEK '#'
#define BRAK '%'
#define PRZESUNIECIE_TRZECH_KROPEK 3
#define PRZESUNIECIE_INTERPUNKCYJNE 1

struct tlumaczenie
{
	char wyraz[ILOSC_LITER];
	char tlumaczony_wyraz[ILOSC_LITER];

	tlumaczenie *next;
};

struct tablica_wyrazow
{
	tlumaczenie *first;
};

struct do_wypisania
{
	char tlumaczony_wyraz[ILOSC_LITER];

	do_wypisania *next;
};

int make_hash(char slowo[])
{
	int index = 0;
	for (int i = 0; i < ILOSC_LITER; i++)
	{
		if (slowo[i] == NULL)
		{
			break;
		}
		index += ((int)slowo[i] << i);
	}
	return index % ROZMIAR;
}

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

int main()
{
	/*std::ifstream in("13.in");
	std::streambuf *cinbuf = std::cin.rdbuf();
	std::cin.rdbuf(in.rdbuf());

	fstream cout;
	cout.open("out.txt", ios::app);*/

	tablica_wyrazow *slownik[ROZMIAR];
	for (int i = 0; i < ROZMIAR; i++)
	{
		slownik[i] = NULL;
	}

	do_wypisania *lista = new do_wypisania;
	lista->next = NULL;
	int ktore_miejsce_listy = 1;
	int index;
	char slowo[ILOSC_LITER];

	while (cin >> slowo/* && cin.get() == ' ' && cin.peek() == '\n'*/)
	{
		if (slowo[0] >= POCZATEK_MALYCH_LITER && slowo[0] <= KONIEC_MALYCH_LITER)
		{
			index = make_hash(slowo); //wybieram index

			if (slownik[index] == NULL)
			{
				tlumaczenie *fraza = new tlumaczenie;
				for (int i = 0; i < ILOSC_LITER; i++)
				{
					if (slowo[i] == NULL)
					{
						fraza->wyraz[i] = NULL;
						break;
					}
					fraza->wyraz[i] = slowo[i];
				}

				cin >> slowo; //tlumaczenie
				for (int i = 0; i < ILOSC_LITER; i++)
				{
					if (slowo[i] == NULL)
					{
						fraza->tlumaczony_wyraz[i] = NULL;
						break;
					}
					fraza->tlumaczony_wyraz[i] = slowo[i];
				}
				fraza->next = NULL;

				slownik[index] = new tablica_wyrazow;
				slownik[index]->first = fraza;
			}
			else
			{
				tlumaczenie *fraza = new tlumaczenie;
				for (int i = 0; i < ILOSC_LITER; i++)
				{
					if (slowo[i] == NULL)
					{
						fraza->wyraz[i] = NULL;
						break;
					}
					fraza->wyraz[i] = slowo[i];
				}

				cin >> slowo; //tlumaczenie
				for (int i = 0; i < ILOSC_LITER; i++)
				{
					if (slowo[i] == NULL)
					{
						fraza->tlumaczony_wyraz[i] = NULL;
						break;
					}
					fraza->tlumaczony_wyraz[i] = slowo[i];
				}
				fraza->next = NULL;
				tlumaczenie *obecny = slownik[index]->first;
				while (obecny->next != NULL)
				{
					obecny = obecny->next;
				}
				obecny->next = fraza;
			}
		}
		else ///TUTAJ TLUMACZE JUZ +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		{
			bool duza_litera = false;
			bool czy_wypisywac = true;
			int ktore_slowo_z_listy;
			bool czy_jest_znak = false;
			char znak;
			int usuwam_interpunkcje = 0;

			if (slowo[0] >= POCZATEK_DUZYCH_LITER && slowo[0] <= KONIEC_DUZYCH_LITER)
			{
				duza_litera = true;
				int zmiana_litery = (int)slowo[0] + 32;
				slowo[0] = (char)zmiana_litery;
			}

			if (czy_interpunkcja(slowo) != BRAK)
			{
				czy_jest_znak = true;
			}
			else
				czy_jest_znak = false;

			if (czy_jest_znak == true)
			{
				znak = czy_interpunkcja(slowo);
				if (znak == TRZYKROPEK)
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

			index = make_hash(slowo);

			if (slownik[index] != NULL)
			{
				tlumaczenie *obecny = slownik[index]->first;
				while (obecny != NULL)
				{
					if (strcmp(slowo, obecny->wyraz) == 0)
					{
						break;
					}
					obecny = obecny->next;
				}
				if (obecny != NULL)
				{
					for (int i = 0; i < ILOSC_LITER; i++)
					{
						if (obecny->tlumaczony_wyraz[i] == NULL)
						{
							if (czy_jest_znak)
							{
								if (znak != TRZYKROPEK)
								{
									lista->tlumaczony_wyraz[i] = znak;
									lista->tlumaczony_wyraz[i + PRZESUNIECIE_INTERPUNKCYJNE] = NULL;
									czy_jest_znak = false;
									break;
								}
								else
								{
									//cout << "Jestem tu" << endl;
									for (int przesuwam_index = 0; przesuwam_index < PRZESUNIECIE_TRZECH_KROPEK; przesuwam_index++)
									{
										lista->tlumaczony_wyraz[i + przesuwam_index] = '.';
									}
									lista->tlumaczony_wyraz[i + PRZESUNIECIE_TRZECH_KROPEK] = NULL;
									czy_jest_znak = false;
									break;
								}
							}
							else
							{
								lista->tlumaczony_wyraz[i] = NULL;
								break;
							}
						}
						//cout << index << endl;
						//cout << i << endl;
						lista->tlumaczony_wyraz[i] = obecny->tlumaczony_wyraz[i];
					}
					//cout << lista->tlumaczony_wyraz << endl;

					if (duza_litera == true)
					{
						int zmiana_litery = (int)lista->tlumaczony_wyraz[0] - 32;
						lista->tlumaczony_wyraz[0] = (char)zmiana_litery;
					}
				}
				else
				{
					if (czy_interpunkcja(slowo) != BRAK)
					{
						czy_jest_znak = true;
					}
					else
						czy_jest_znak = false;

					if (czy_jest_znak == true)
					{
						znak = czy_interpunkcja(slowo);
						if (znak == TRZYKROPEK)
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

					czy_wypisywac = false;
					cout << "Brak slow: ";
					cout << slowo << " ";
					czy_jest_znak = false;
				}
			}
			else
			{
				if (czy_interpunkcja(slowo) != BRAK)
				{
					czy_jest_znak = true;
				}
				else
					czy_jest_znak = false;

				if (czy_jest_znak == true)
				{
					znak = czy_interpunkcja(slowo);
					if (znak == TRZYKROPEK)
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
				czy_wypisywac = false;
				cout << "Brak slow: ";
				cout << slowo << " ";
				czy_jest_znak = false;
			}

			do_wypisania *poczatek_lista = lista;
			czy_jest_znak = false;
			if (cin.get() == ' ' && cin.peek() != '\n')
			{
				while (cin >> slowo)
				{
					duza_litera = false;

					if (slowo[0] >= POCZATEK_DUZYCH_LITER && slowo[0] <= KONIEC_DUZYCH_LITER)
					{
						int zmiana_litery = (int)slowo[0] + 32;
						slowo[0] = (char)zmiana_litery;
						duza_litera = true;
					}

					if (slowo[0] != MYSLNIK)
					{
						if (czy_interpunkcja(slowo) != BRAK)
						{
							czy_jest_znak = true;
						}
						else
							czy_jest_znak = false;

						if (czy_jest_znak == true)
						{
							znak = czy_interpunkcja(slowo);
							if (znak == TRZYKROPEK)
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
						index = make_hash(slowo);

						if (slownik[index] != NULL && slownik[index]->first != NULL)
						{
							tlumaczenie *obecny = slownik[index]->first;
							while (obecny != NULL)
							{
								if (strcmp(slowo, obecny->wyraz) == 0)
									break;
								obecny = obecny->next;
							}
							if (obecny != NULL)
							{
								do_wypisania *nowy = new do_wypisania;
								nowy->next = NULL;

								for (int i = 0; i < ILOSC_LITER; i++)
								{
									if (obecny->tlumaczony_wyraz[i] == NULL)
									{
										if (czy_jest_znak)
										{
											if (znak != TRZYKROPEK)
											{
												nowy->tlumaczony_wyraz[i] = znak;
												nowy->tlumaczony_wyraz[i + PRZESUNIECIE_INTERPUNKCYJNE] = NULL;
												czy_jest_znak = false;
												break;
											}
											else
											{
												for (int przesuwam_index = 0; przesuwam_index < PRZESUNIECIE_TRZECH_KROPEK; przesuwam_index++)
												{
													nowy->tlumaczony_wyraz[i + przesuwam_index] = '.';
												}
												nowy->tlumaczony_wyraz[i + PRZESUNIECIE_TRZECH_KROPEK] = NULL;
												czy_jest_znak = false;
												break;
											}
										}
										else
										{
											nowy->tlumaczony_wyraz[i] = NULL;
											break;
										}
									}
									nowy->tlumaczony_wyraz[i] = obecny->tlumaczony_wyraz[i];
								}

								if (duza_litera)
								{
									int zmiana_litery = (int)nowy->tlumaczony_wyraz[0] - 32;
									nowy->tlumaczony_wyraz[0] = (char)zmiana_litery;
								}

								lista->next = nowy;
								lista = lista->next;
							}
							else
							{
								if (czy_interpunkcja(slowo) != BRAK)
								{
									czy_jest_znak = true;
								}
								else
									czy_jest_znak = false;

								if (czy_jest_znak == true)
								{
									znak = czy_interpunkcja(slowo);
									if (znak == TRZYKROPEK)
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
								if (czy_wypisywac != false)
								{
									czy_wypisywac = false;
									cout << "Brak slow: ";
								}
								cout << slowo << " ";
							}
						}
						else
						{
							if (czy_interpunkcja(slowo) != BRAK)
							{
								czy_jest_znak = true;
							}
							else
								czy_jest_znak = false;

							if (czy_jest_znak == true)
							{
								znak = czy_interpunkcja(slowo);
								if (znak == TRZYKROPEK)
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
							if (czy_wypisywac != false)
							{
								czy_wypisywac = false;
								cout << "Brak slow: ";
							}
							cout << slowo << " ";
						}
						duza_litera = false;
						czy_jest_znak = false;
					}
					else
					{
						do_wypisania *nowy = new do_wypisania;
						nowy->next = NULL;
						nowy->tlumaczony_wyraz[0] = slowo[0];
						nowy->tlumaczony_wyraz[1] = NULL;
						lista->next = nowy;
						lista = lista->next;
					}

					if (cin.get() == ' ' && cin.peek() == '\n')
					{
						if (czy_wypisywac == true)
						{
							while (poczatek_lista != NULL)
							{
								cout << poczatek_lista->tlumaczony_wyraz << " ";
								poczatek_lista = poczatek_lista->next;
							}
						}
						cout << endl;
						break;
					}
				}
			}
			else
			{
				if (czy_wypisywac == true)
				{
					while (poczatek_lista != NULL)
					{
						cout << poczatek_lista->tlumaczony_wyraz << " ";
						poczatek_lista = poczatek_lista->next;
					}
				}
				cout << endl;
			}
			//system("pause");
		}
	}

	//cout.close();
	//system("pause");
	return 0;
}
