#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct lista
{
	lista *next = NULL, *before = NULL;
	int data;

	/*lista::lista()
	{
		lista *next = NULL, *before = NULL;
		int data;
	}*/
};


void show(lista * pierwszy)
{
	while (pierwszy != NULL)
	{
		printf("%d\n", pierwszy->data);
		pierwszy = pierwszy->next;
	}
}

void insert(lista* pierwszy, int new_one)
{
	lista *nowy;
	nowy = new lista;

	nowy->data = pierwszy->data;
	nowy->next = pierwszy->next;
	pierwszy->next->before = nowy;
	pierwszy->data = new_one;
	pierwszy->next = nowy;


	//nowy->data = new_one;
	//nowy->next = pierwszy;
	//pierwszy->before = nowy;
}


int main()
{
	int kkk = 10;

	lista *first;
	lista *second;
	lista *third;

	first = new lista;
	second = new lista;
	third = new lista;

	first->data = 2;
	second->data = 3;
	third->data = 4;

	first->next = second;
	second->next = third;
	third->before = second;
	second->before = first;

	insert(first, kkk);
	show(first);


	system("PAUSE");
	return 0;
}