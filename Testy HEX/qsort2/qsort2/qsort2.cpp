#include <iostream>
using namespace std;

void quickSortsort(int array[], int start, int end)
{
	int i = start;                          // index of left-to-right scan
	int k = end;                            // index of right-to-left scan
	for (int i = 0; i < end; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	if (end - start >= 1)                   // check that there are at least two elements to sort
	{
		int pivot = array[start];       // set the pivot as the first element in the partition

		while (k > i)                   // while the scan indices from left and right have not met,
		{
			while (array[i] <= pivot && i <= end && k > i)  // from the left, look for the first
				i++;                                    // element greater than the pivot
			while (array[k] > pivot && k >= start && k >= i) // from the right, look for the first
				k--;                                        // element not greater than the pivot
			if (k > i)                                       // if the left seekindex is still smaller than
				swap(array[i], array[k]);                      // the right index, swap the corresponding elements
		}
		swap(array[start], array[k]);          // after the indices have crossed, swap the last element in
		// the left partition with the pivot 
		cout << left << "-" << (start + end) / 2 << "-" << right << " ";
		for (int k = 0; k < end - 1; k++)
		{
			cout << array[k] << " ";
		}
		cout << endl;
		quickSortsort(array, start, k - 1); // quicksort the left partition
		quickSortsort(array, k + 1, end);   // quicksort the right partition
	}
	else    // if there is only one element in the partition, do not do any sorting
	{
		for (int k = 0; k < end - 1; k++)
		{
			cout << array[k] << " ";
		}
		cout << endl;
		return;                     // the array is sorted, so exit
	}
}

void quickSort(int array[], int size)
// pre: array is full, all elements are non-null integers
// post: the array is sorted in ascending order
{
	quickSortsort(array, 0, size);              // quicksort all the elements in the array
}

int main()
{
	int size;
	int liczba;
	int *wsk;
	//int temp;
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
		quickSort(wsk, size);

	}
	//system("pause");
	return 0;
}