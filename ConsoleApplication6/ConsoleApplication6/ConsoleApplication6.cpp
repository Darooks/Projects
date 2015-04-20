#include <iostream>
using namespace std;

//int B(int*);
int a = 1;

int A(int *b)
{
	cout << *b << endl;
	*b = *b + a;
	cout << a << endl;
	cout << *b << endl;
	
	return *b;
}

int B(int a)
{
	int b = 3;
	cout << a << endl;
	a = a
		+
		A(&b);
	cout << b << endl;
	cout << a << endl;
	return b;
}

int main()
{
	//cout << a << endl;
	a = A(&a) + B(4);
	cout << "a = " << a << endl;

	return 0;
}