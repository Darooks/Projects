#include <iostream>

using namespace std;

void quicksort(int array[], int left, int right, int size)
{
	int i = left;
	int j = right;
	int tmp;
	int pivot = array[left];
	
	/*if (right - left == 0)
	{
		for (int k = 0; k < right; k++)
		{
			cout << array[k] << " ";
		}
		cout << endl;
		return;
	}*/

	if (right - left >= 1)
	{
		while (i < j)
		{
			while (array[i] <= pivot && i <= right && j > i)
				i++;
			while (array[j] > pivot && j >= left && j >= i)
				j--;

			if (i < j)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
				i++;
				j--;
			}
			//swap(array[left], array[right]);
			if (i < right)
			{
				quicksort(array, i, right, size);
			}
			if (left < j)
			{
				quicksort(array, left, j, size);
			}
			

		}
		cout << left << "-" << (left + right) / 2 << "-" << right << " ";
		for (int k = 0; k < right + 1; k++)
		{
			cout << array[k] << " ";
		}
		cout << endl;
	}
	else
	{
		for (int k = 0; k < right; k++)
		{
			cout << array[k] << " ";
		}
		cout << endl;
		return;
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
		quicksort(wsk, 0, size - 1, size);
	}

	system("pause");
	return 0;
}