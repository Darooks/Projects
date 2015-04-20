#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <mutex>

//---------------------------------------------------------------------------
#pragma argsused
struct dane_dla_watku // tablica zawiera dane, ktore otrzymaja w¹tki
{
	char nazwa[50];
	int parametr;
	int id;
} dane[3] = { { "[1]", 5, 1 }, { "[2]", 8, 2 },
{ "[3]", 12, 3 } };

// priorytety w¹tków
int priorytety[3] = { THREAD_PRIORITY_BELOW_NORMAL,
THREAD_PRIORITY_NORMAL, THREAD_PRIORITY_ABOVE_NORMAL };

HANDLE watki[3]; // dojœcia (uchwyty) w¹tków
// deklaracja funkcji w¹tku

DWORD WINAPI funkcja_watku(void *argumenty);

HANDLE gateKeeper;
//---------------------------------------------------------------------------
int main(int argc, char **argv)
{
	gateKeeper = CreateMutex(NULL, FALSE, NULL);
	WaitForSingleObject(gateKeeper, INFINITE);

	int i;
	DWORD id; // identyfikator w¹tku
	system("cls");
	printf("Uruchomienie programu\n");
	// tworzenie w¹tków
	for (i = 0; i < 3; i++)
	{
		watki[i] = CreateThread(
			NULL, // atrybuty bezpieczeñstwa
			0, // inicjalna wielkoœæ stosu
			funkcja_watku, // funkcja w¹tku
			(void *)&dane[i],// dane dla funkcji w¹tku
			0, // flagi utworzenia
			&id);
		if (watki[i] != INVALID_HANDLE_VALUE)
		{
			printf("Utworzylem watek %s o identyfikatorze %x\n",
				dane[i].nazwa, id);
			// ustawienie priorytetu
			SetThreadPriority(watki[i], priorytety[i]);
		}
	}
	ReleaseMutex(gateKeeper);

	WaitForMultipleObjects(3, watki, TRUE, INFINITE);
	Sleep(20000); // uœpienie w¹tku g³ównego na 20 s
	for (int i = 0; i < 3; i++)
	{
		CloseHandle(watki[i]);
	}
	CloseHandle(gateKeeper);
	ReleaseMutex(gateKeeper);

	return 0;
}

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//---------------------------------------------------------------------------
// trzy takie funkcje pracuj¹ wspó³bie¿nie w programie
DWORD WINAPI funkcja_watku(void *argumenty)
{
	unsigned int licznik = 0;
	// rzutowanie struktury na w³asny wskaŸnik
	struct dane_dla_watku *moje_dane = (struct dane_dla_watku *)argumenty;
	// wyœwietlenie informacji o uruchomieniu
	WaitForSingleObject(gateKeeper, INFINITE);
	gotoxy(1, moje_dane->parametr);
	printf("%s", moje_dane->nazwa);
	ReleaseMutex(gateKeeper);
	//Sleep(1000);

	// praca, w¹tki sa terminowane przez zakoñczenie programu
	// - funkcji main
	while (1)
	{
		WaitForSingleObject(gateKeeper, INFINITE);
		gotoxy(licznik++ / 5000 + 5, moje_dane->parametr);
		printf("%d", moje_dane->id);
		ReleaseMutex(gateKeeper);
	}

	return 0;
}
//