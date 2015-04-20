#include <iostream>
#include <conio.h>
using namespace std;
void max_heapify(int *a, int i, int n)
{
	int j, temp;
	temp = a[i];
	j = 2 * i;
	while (j <= n)
	{
		if (j < n && a[j + 1] > a[j])
			j = j + 1;
		if (temp > a[j])
			break;
		else if (temp <= a[j])
		{
			a[j / 2] = a[j];
			j = 2 * j;
		}
	}
	a[j / 2] = temp;
	for (int j = 0; j < n; j++)
		cout << a[j] << " ";
	cout << endl;
	return;
}
void heapsort(int *a, int n)
{
	int i, temp;
	for (i = n; i >= 2; i--)
	{
		temp = a[i];
		a[i] = a[1];
		a[1] = temp;
		max_heapify(a, 1, i - 1);
	}
}
void build_maxheap(int *a, int n)
{
	int i;
	for (i = n / 2; i >= 1; i--)
	{
		max_heapify(a, i, n);
	}
}
int main()
{
	int size;
	int liczba;
	int *wsk;
	int temp;
	static int licznik = 0;
	while (cin >> size)
	{
		wsk = new int[size];
		while (true)
		{
			if (licznik >= size)
			{
				licznik = 0;
				break;
			}
			cin >> liczba;
			wsk[licznik] = liczba;
			licznik++;
		}
		//quicksort(wsk, 0, size - 1, size);
		build_maxheap(wsk, size);
		heapsort(wsk, size);
	}

	system("pause");
	return 0;
}
