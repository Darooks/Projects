#include<iostream>
using namespace std;

int partition(int array[], int p, int r);
void quicksort(int array[], int wall, int r);

int main()
{
	int ilosc_liczb, i;
	int array[3000];
	while (cin >> ilosc_liczb)
	{
		for (i = 0; i < ilosc_liczb; i++)
		{
			cin >> array[i];
		}
		quicksort(array, 0, ilosc_liczb - 1);
	}
	return 0;
}

int partition(int array[], int p, int right)
{
	int x = array[p];
	int i = p; 
	int j = right; 
	while (true)
	{
		while (array[j] > x)
			j--;
		while (array[i] < x)
			i++;
		if (i < j)
		{
			swap(array[i], array[j]);
			i++;
			j--;
		}
		else
		{
			return j;
		}
	}
}

void quicksort(int array[], int wall, int right)
{
	int leaf;
	if (wall < right)
	{
		leaf = partition(array, wall, right);
		cout << wall << "-" << leaf << "-" << right;
		for (int i = wall; i <= right; i++)
		{
			cout << " " << array[i];
		}
		cout << endl;
		quicksort(array, wall, leaf);
		quicksort(array, leaf + 1, right);
	}
	else if (wall == right)
	{
		cout << wall << " " << array[wall] << endl;
	}
}