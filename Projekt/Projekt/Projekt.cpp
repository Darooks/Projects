#include <iostream>
#include <fstream>
using namespace std;

#define SZEROKOSC_MAPY 66
#define WYSOKOSC_MAPY 25
#define DLUGOSC_KOMENDY 24
#define KLASYCZNY_HEX 12
#define WYGRAL_NIEBIESKI 'b'
#define WYGRAL_CZERWONY 'r'
#define REMIS 'n'

int wysokosc_planszy(char kwadrat_hex[KLASYCZNY_HEX][KLASYCZNY_HEX])
{
	int wysokosc_hexa = 0;
	for (int i = 0; i < KLASYCZNY_HEX; i++)
	{
		if (kwadrat_hex[i][0] == NULL)
		{
			break;
		}
		wysokosc_hexa++;
	}
	return wysokosc_hexa;
}

int pioneczki(char kwadrat_hex[KLASYCZNY_HEX][KLASYCZNY_HEX])
{
	int ilosc_pionkow = 0;
	for (int i = 0; i < wysokosc_planszy(kwadrat_hex); i++)
	{
		for (int j = 0; j < wysokosc_planszy(kwadrat_hex); j++)
		{
			if (kwadrat_hex[i][j] == 'r' || kwadrat_hex[i][j] == 'b')
			{
				ilosc_pionkow++;
			}
		}
	}
	return ilosc_pionkow;
}

int pionkow_red(char kwadrat_hex[KLASYCZNY_HEX][KLASYCZNY_HEX])
{
	int ilosc_pionkow = 0;
	for (int i = 0; i < wysokosc_planszy(kwadrat_hex); i++)
	{
		for (int j = 0; j < wysokosc_planszy(kwadrat_hex); j++)
		{
			if (kwadrat_hex[i][j] == 'r')
			{
				ilosc_pionkow++;
			}
		}
	}
	return ilosc_pionkow;
}

int pionkow_blue(char kwadrat_hex[KLASYCZNY_HEX][KLASYCZNY_HEX])
{
	int ilosc_pionkow = 0;
	for (int i = 0; i < wysokosc_planszy(kwadrat_hex); i++)
	{
		for (int j = 0; j < wysokosc_planszy(kwadrat_hex); j++)
		{
			if (kwadrat_hex[i][j] == 'b')
			{
				ilosc_pionkow++;
			}
		}
	}
	return ilosc_pionkow;
}

bool czy_poprawna(char kwadrat_hex[KLASYCZNY_HEX][KLASYCZNY_HEX]) //0 dla board correct, 1 dla board possible
{
	int ilosc_czerwonych = 0;
	int ilosc_niebieskich = 0;
	for (int i = 0; i < wysokosc_planszy(kwadrat_hex); i++)
	{
		for (int j = 0; j < wysokosc_planszy(kwadrat_hex); j++)
		{
			if (kwadrat_hex[i][j] == 'r')
			{
				ilosc_czerwonych++;
			}
			else if (kwadrat_hex[i][j] == 'b')
			{
				ilosc_niebieskich++;
			}
		}
	}


	if (ilosc_czerwonych == ilosc_niebieskich || ilosc_czerwonych - 1 == ilosc_niebieskich)
	{
		//cout << "YES" << endl;
		return true;
	}
	else
	{
		//cout << "NO" << endl;
		return false;
	}
	return false;
}

bool czy_poprawna_wygrana(char kwadrat_hex[KLASYCZNY_HEX][KLASYCZNY_HEX], char kto_wygral) //wygrana z kazdego z pionkow
{                                                                                                                                                                                       //to zawsze inne warunki
	int ilosc_czerwonych = 0;
	int ilosc_niebieskich = 0;
	for (int i = 0; i < wysokosc_planszy(kwadrat_hex); i++)
	{
		for (int j = 0; j < wysokosc_planszy(kwadrat_hex); j++)
		{
			if (kwadrat_hex[i][j] == 'r')
			{
				ilosc_czerwonych++;
			}
			else if (kwadrat_hex[i][j] == 'b')
			{
				ilosc_niebieskich++;
			}
		}
	}

	if (kto_wygral == WYGRAL_CZERWONY)
	{
		if (ilosc_czerwonych - 1 == ilosc_niebieskich)
		{
			//cout << "YES" << endl;
			return true;
		}
		else
		{
			//cout << "NO" << endl;
			return false;
		}
		return false;
	}

	else if (kto_wygral == WYGRAL_NIEBIESKI)
	{
		if (ilosc_czerwonych == ilosc_niebieskich)
		{
			//cout << "YES" << endl;
			return true;
		}
		else
		{
			//cout << "NO" << endl;
			return false;
		}
		return false;
	}
	else if (kto_wygral == REMIS)
	{

		if (ilosc_czerwonych == ilosc_niebieskich || ilosc_czerwonych - 1 == ilosc_niebieskich)
		{
			//cout << "YES" << endl;
			return true;
		}
		else
		{
			//cout << "NO" << endl;
			return false;
		}
		return false;
	}
	return false;
}

bool czy_wygral_czerwony(int sprawdzam_x, int sprawdzam_y, char kwadrat_hex[KLASYCZNY_HEX][KLASYCZNY_HEX], bool **sprawdzony)
{
	if (sprawdzam_x < wysokosc_planszy(kwadrat_hex) && sprawdzam_y < wysokosc_planszy(kwadrat_hex) && sprawdzam_x >= 0 && sprawdzam_y >= 0) //dla niebieskiego x sie zmniejsza, dla czerwonego y:
	{                                                                                                                                                                                                                                       //trzeba uwazac by nie przekroczyl --> 0!!!
		if (sprawdzony[sprawdzam_y][sprawdzam_x])
			return false;

		sprawdzony[sprawdzam_y][sprawdzam_x] = true;
		if (kwadrat_hex[sprawdzam_y][sprawdzam_x] == 'r' && sprawdzam_x == wysokosc_planszy(kwadrat_hex) - 1)
		{
			return true;
		}
		else if (kwadrat_hex[sprawdzam_y][sprawdzam_x] == 'r')
		{
			if (czy_wygral_czerwony(sprawdzam_x - 1, sprawdzam_y - 1, kwadrat_hex, sprawdzony) == true)
				return true;
			if (czy_wygral_czerwony(sprawdzam_x - 1, sprawdzam_y, kwadrat_hex, sprawdzony) == true)
				return true;
			if (czy_wygral_czerwony(sprawdzam_x, sprawdzam_y + 1, kwadrat_hex, sprawdzony) == true)
				return true;
			if (czy_wygral_czerwony(sprawdzam_x, sprawdzam_y - 1, kwadrat_hex, sprawdzony) == true)
				return true;
			if (czy_wygral_czerwony(sprawdzam_x + 1, sprawdzam_y, kwadrat_hex, sprawdzony) == true)
				return true;
			if (czy_wygral_czerwony(sprawdzam_x + 1, sprawdzam_y + 1, kwadrat_hex, sprawdzony) == true)
				return true;
		}
	}
	return false;
}

bool czy_wygral_niebieski(int sprawdzam_x, int sprawdzam_y, char kwadrat_hex[KLASYCZNY_HEX][KLASYCZNY_HEX], bool **sprawdzony)
{
	if (sprawdzam_x < wysokosc_planszy(kwadrat_hex) && sprawdzam_y < wysokosc_planszy(kwadrat_hex) && sprawdzam_x >= 0 && sprawdzam_y >= 0) //dla niebieskiego x sie zmniejsza, dla czerwonego y:
	{                                                                                                                                                                                                                                       //trzeba uwazac by nie przekroczyl --> 0!!!
		if (sprawdzony[sprawdzam_y][sprawdzam_x])
			return false;

		sprawdzony[sprawdzam_y][sprawdzam_x] = true;
		if (kwadrat_hex[sprawdzam_y][sprawdzam_x] == 'b' && sprawdzam_y == wysokosc_planszy(kwadrat_hex) - 1)
		{
			return true;
		}
		else if (kwadrat_hex[sprawdzam_y][sprawdzam_x] == 'b')
		{
			if (sprawdzam_y == 0)
			{
				if (czy_wygral_niebieski(sprawdzam_x - 1, sprawdzam_y - 1, kwadrat_hex, sprawdzony) == true)
					return true;
				if (czy_wygral_niebieski(sprawdzam_x, sprawdzam_y + 1, kwadrat_hex, sprawdzony) == true)
					return true;
				if (czy_wygral_niebieski(sprawdzam_x, sprawdzam_y - 1, kwadrat_hex, sprawdzony) == true)
					return true;
				if (czy_wygral_niebieski(sprawdzam_x + 1, sprawdzam_y + 1, kwadrat_hex, sprawdzony) == true)
					return true;
			}
			else
			{
				if (czy_wygral_niebieski(sprawdzam_x - 1, sprawdzam_y - 1, kwadrat_hex, sprawdzony) == true)
					return true;
				if (czy_wygral_niebieski(sprawdzam_x - 1, sprawdzam_y, kwadrat_hex, sprawdzony) == true)
					return true;
				if (czy_wygral_niebieski(sprawdzam_x, sprawdzam_y + 1, kwadrat_hex, sprawdzony) == true)
					return true;
				if (czy_wygral_niebieski(sprawdzam_x, sprawdzam_y - 1, kwadrat_hex, sprawdzony) == true)
					return true;
				if (czy_wygral_niebieski(sprawdzam_x + 1, sprawdzam_y, kwadrat_hex, sprawdzony) == true)
					return true;
				if (czy_wygral_niebieski(sprawdzam_x + 1, sprawdzam_y + 1, kwadrat_hex, sprawdzony) == true)
					return true;
			}

		}
	}
	return false;
}

char czy_skonczona(char kwadrat_hex[KLASYCZNY_HEX][KLASYCZNY_HEX]) // FUNKCJA OTWIERA PANEL DO ZARZADZANIA BATERIA!!!
{
	bool **sprawdzony = new bool*[wysokosc_planszy(kwadrat_hex)];
	for (int i = 0; i < wysokosc_planszy(kwadrat_hex); i++)
	{
		sprawdzony[i] = new bool[wysokosc_planszy(kwadrat_hex)];
	}

	//sprawdzam czy r wygral
	bool czy_wygral_red = false;
	bool czy_wygral_blue = false;
	//cout << "x---> " << sprawdzam_x << " |" << " y---> " << sprawdzam_y << " | " << "znak--->" << kwadrat_hex[sprawdzam_y][sprawdzam_x] << endl;
	if (czy_poprawna(kwadrat_hex))
	{
		for (int sprawdzam_y = 0; sprawdzam_y < wysokosc_planszy(kwadrat_hex); sprawdzam_y++)
		{
			for (int y = 0; y < wysokosc_planszy(kwadrat_hex); y++)
			{
				for (int x = 0; x < wysokosc_planszy(kwadrat_hex); x++)
				{
					sprawdzony[y][x] = false;
				}
			}
			if (kwadrat_hex[sprawdzam_y][0] == 'r')
			{
				czy_wygral_red = czy_wygral_czerwony(0, sprawdzam_y, kwadrat_hex, sprawdzony);
				if (czy_wygral_red)
				{
					break;
				}
			}
		}

		if (!czy_wygral_red)
		{
			for (int sprawdzam_x = 0; sprawdzam_x < wysokosc_planszy(kwadrat_hex); sprawdzam_x++)
			{
				for (int y = 0; y < wysokosc_planszy(kwadrat_hex); y++)
				{
					for (int x = 0; x < wysokosc_planszy(kwadrat_hex); x++)
					{
						sprawdzony[y][x] = false;
					}
				}
				if (kwadrat_hex[0][sprawdzam_x] == 'b')
				{
					czy_wygral_blue = czy_wygral_niebieski(sprawdzam_x, 0, kwadrat_hex, sprawdzony);
					if (czy_wygral_blue)
					{
						break;
					}
				}
			}
		}
	}

	if (czy_wygral_red == true)
	{
		return WYGRAL_CZERWONY;
	}
	else if (czy_wygral_blue == true)
	{
		return WYGRAL_NIEBIESKI;
	}
	else
	{
		return REMIS;
	}
	return REMIS;
}

void pokazplansze(char kwadrat_hex[KLASYCZNY_HEX][KLASYCZNY_HEX])
{
	for (int y = 0; y < wysokosc_planszy(kwadrat_hex); y++)
	{
		for (int x = 0; x < wysokosc_planszy(kwadrat_hex); x++)
		{
			cout << kwadrat_hex[y][x] << " ";
		}
		cout << endl;
	}
}

bool is_board_possible(char kwadrat_hex[KLASYCZNY_HEX][KLASYCZNY_HEX])
{
	char kto_wygral = czy_skonczona(kwadrat_hex);
	bool poprawna_wygrana = false;
	bool poprawna_wygrana_red = false;
	bool poprawna_wygrana_blue = false;
	int ilosc_wygranych = 0;

	bool czy_wygral_red = false;
	bool czy_wygral_blue = false;
	bool byla_wygrana_red = false;
	bool byla_wygrana_blue = false;

	bool **sprawdzony = new bool*[wysokosc_planszy(kwadrat_hex)];
	for (int i = 0; i < wysokosc_planszy(kwadrat_hex); i++)
	{
		sprawdzony[i] = new bool[wysokosc_planszy(kwadrat_hex)];
	}

	//Czy ilosc pionkow jest poprawna
	if (czy_poprawna(kwadrat_hex) == true)
	{
		for (int sprawdzam_y_red = 0; sprawdzam_y_red < wysokosc_planszy(kwadrat_hex); sprawdzam_y_red++)
		{
			for (int y = 0; y < wysokosc_planszy(kwadrat_hex); y++)
			{
				for (int x = 0; x < wysokosc_planszy(kwadrat_hex); x++)
				{
					sprawdzony[y][x] = false;
				}
			}
			if (kwadrat_hex[sprawdzam_y_red][0] == 'r')
			{
				czy_wygral_red = czy_wygral_czerwony(0, sprawdzam_y_red, kwadrat_hex, sprawdzony);
				if (czy_wygral_red)
				{
					byla_wygrana_red = true;
					break;
				}
			}
		}

		for (int sprawdzam_x_blue = 0; sprawdzam_x_blue < wysokosc_planszy(kwadrat_hex); sprawdzam_x_blue++)
		{
			for (int y = 0; y < wysokosc_planszy(kwadrat_hex); y++)
			{
				for (int x = 0; x < wysokosc_planszy(kwadrat_hex); x++)
				{
					sprawdzony[y][x] = false;
				}
			}
			if (kwadrat_hex[0][sprawdzam_x_blue] == 'b')
			{
				czy_wygral_blue = czy_wygral_niebieski(sprawdzam_x_blue, 0, kwadrat_hex, sprawdzony);
				if (czy_wygral_blue)
				{
					byla_wygrana_blue = true;
					break;
				}
			}
		}

		if (byla_wygrana_red == true && byla_wygrana_blue == false)
		{
			for (int sprawdzam_y = 0; sprawdzam_y < wysokosc_planszy(kwadrat_hex); sprawdzam_y++)
			{
				if (poprawna_wygrana_red == true)
					break;

				for (int sprawdzam_x = 0; sprawdzam_x < wysokosc_planszy(kwadrat_hex); sprawdzam_x++)
				{
					if (poprawna_wygrana_red == true)
						break;

					if (kwadrat_hex[sprawdzam_y][sprawdzam_x] == 'r')
					{
						kwadrat_hex[sprawdzam_y][sprawdzam_x] = ' ';
						ilosc_wygranych = 0;
						for (int sprawdzam_wygrana_red = 0; sprawdzam_wygrana_red < wysokosc_planszy(kwadrat_hex); sprawdzam_wygrana_red++)
						{
							for (int y = 0; y < wysokosc_planszy(kwadrat_hex); y++)
							{
								for (int x = 0; x < wysokosc_planszy(kwadrat_hex); x++)
								{
									sprawdzony[y][x] = false;
								}
							}
							czy_wygral_red = czy_wygral_czerwony(0, sprawdzam_wygrana_red, kwadrat_hex, sprawdzony);
							if (czy_wygral_red)
								ilosc_wygranych++;
						}
						kwadrat_hex[sprawdzam_y][sprawdzam_x] = 'r';
						if (ilosc_wygranych == 0)
						{
							if (pionkow_red(kwadrat_hex) == pionkow_blue(kwadrat_hex) + 1)
								poprawna_wygrana_red = true;
							else
								return false;
						}
					}
				}
			}
		}

		else if (byla_wygrana_red == false && byla_wygrana_blue == true)
		{
			for (int sprawdzam_y = 0; sprawdzam_y < wysokosc_planszy(kwadrat_hex); sprawdzam_y++)
			{
				if (poprawna_wygrana_blue == true)
					break;

				for (int sprawdzam_x = 0; sprawdzam_x < wysokosc_planszy(kwadrat_hex); sprawdzam_x++)
				{
					if (poprawna_wygrana_blue == true)
						break;

					if (kwadrat_hex[sprawdzam_y][sprawdzam_x] == 'b')
					{
						kwadrat_hex[sprawdzam_y][sprawdzam_x] = ' ';
						ilosc_wygranych = 0;
						for (int sprawdzam_wygrana_blue = 0; sprawdzam_wygrana_blue < wysokosc_planszy(kwadrat_hex); sprawdzam_wygrana_blue++)
						{
							for (int y = 0; y < wysokosc_planszy(kwadrat_hex); y++)
							{
								for (int x = 0; x < wysokosc_planszy(kwadrat_hex); x++)
								{
									sprawdzony[y][x] = false;
								}
							}
							czy_wygral_blue = czy_wygral_niebieski(sprawdzam_wygrana_blue, 0, kwadrat_hex, sprawdzony);
							if (czy_wygral_blue)
							{
								ilosc_wygranych++;
							}
						}
						kwadrat_hex[sprawdzam_y][sprawdzam_x] = 'b';
						if (ilosc_wygranych == 0)
						{
							if (pionkow_red(kwadrat_hex) == pionkow_blue(kwadrat_hex))
								poprawna_wygrana_blue = true;
							else
								return false;
						}
					}
				}
			}
		}

		if (byla_wygrana_red == true && byla_wygrana_blue == false || byla_wygrana_red == false && byla_wygrana_blue == true)
		{
			if (byla_wygrana_red == true && poprawna_wygrana_red == true || byla_wygrana_blue == true && poprawna_wygrana_blue == true)
				poprawna_wygrana = true;
			else
				poprawna_wygrana = false;
		}
		else
			poprawna_wygrana = false;

		if (poprawna_wygrana == true)
		{
			return true;
		}
		else
		{
			if (byla_wygrana_blue == false && byla_wygrana_red == false)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

int main()
{
	/*ifstream in("wejscie.txt");
	streambuf *cinbuf = std::cin.rdbuf();
	cin.rdbuf(in.rdbuf());*/

	char falszywy_hex[SZEROKOSC_MAPY];
	char hex[WYSOKOSC_MAPY][SZEROKOSC_MAPY];
	char kwadrat_hex[KLASYCZNY_HEX][KLASYCZNY_HEX];
	char command[DLUGOSC_KOMENDY];
	char kto_wygral = NULL;
	int wysokosc = 0;
	static int index = 0;
	static int index_y = 0;
	static int kwad_index = 0;
	static int kwad_index_y = 0;
	int tmp_index_y = 0;
	bool pobierz_plansze = false;
	bool poprawna_wygrana = false;

	while (cin.getline(falszywy_hex, SZEROKOSC_MAPY)) //WPISUJEMY DO MOJEJ KOCHANEJ TABLICY MAPKE 
	{
		if (falszywy_hex[0] == NULL)
		{
			continue;
		}

		index = 0;
		if (!isalpha(falszywy_hex[0]))
		{
			for (int i = 0; i < sizeof(falszywy_hex) / sizeof(char); i++)
			{
				if (falszywy_hex[i] == NULL)
				{
					hex[index_y][i] = NULL;
					index_y++;
					break;
				}
				hex[index_y][i] = falszywy_hex[i];
			}
			wysokosc++;
		}
		else
		{
			for (index_y = 0; index_y < wysokosc / 2 + 1; index_y++)
			{
				index = 0;
				while (true)
				{
					if (hex[index_y][index] == NULL)
					{
						break;
					}

					if (hex[index_y][index] == '<')
					{
						index += 2;
						tmp_index_y = index_y;
						while (true)
						{
							if (hex[tmp_index_y][index - 1] == NULL || index > SZEROKOSC_MAPY)
							{
								kwadrat_hex[kwad_index_y][kwad_index] = NULL;
								kwadrat_hex[kwad_index_y + 1][0] = NULL;
								index = 0;

								kwad_index = 0;
								kwad_index_y++;
								break;
							}
							kwadrat_hex[kwad_index_y][kwad_index] = hex[tmp_index_y][index];

							tmp_index_y++;
							index += 3;
							kwad_index++;
						}
						break;
					}
					index++;
				}
			}
			int i = 0;
			while (true)
			{
				if (falszywy_hex[i] == NULL)
				{
					command[i] = NULL;
					break;
				}
				command[i] = falszywy_hex[i];
				i++;
			}

			if (!strcmp(command, "BOARD_SIZE"))
			{
				cout << wysokosc_planszy(kwadrat_hex) << endl;
			}
			else if (!strcmp(command, "PAWNS_NUMBER"))
			{
				cout << pioneczki(kwadrat_hex) << endl;
			}
			else if (!strcmp(command, "IS_BOARD_CORRECT"))
			{
				if (czy_poprawna(kwadrat_hex) == true)
					cout << "YES" << endl;
				else
					cout << "NO" << endl;
			}
			else if (!strcmp(command, "IS_GAME_OVER"))
			{
				kto_wygral = czy_skonczona(kwadrat_hex);
				if (kto_wygral == WYGRAL_CZERWONY)
					cout << "YES RED" << endl;
				else if (kto_wygral == WYGRAL_NIEBIESKI)
					cout << "YES BLUE" << endl;
				else if (kto_wygral == REMIS)
					cout << "NO" << endl;
			}
			else if (!strcmp(command, "IS_BOARD_POSSIBLE"))
			{
				//ofstream plik;
				//plik.open("wyjscie.txt", ios::app);
				poprawna_wygrana = is_board_possible(kwadrat_hex);
				if (poprawna_wygrana)
				{
					cout << "YES" << endl;
					//plik << "YES" << endl << endl;
				}
				else
				{
					cout << "NO" << endl;
					//plik << "NO" << endl << endl;
				}
				//plik.close();
			}

			index_y = 0;
			index = 0;
			kwad_index = 0;
			kwad_index_y = 0;
			wysokosc = 0;

		}

	}
	return 0;
}