#include <iostream>

using namespace std;

void fun(int *x)
{
	cout << "juz" << endl;
	*x = 4;
}

int main()
{
	int *x;
	fun(x);
	cout << x << endl;
	
	
	


	
	system("pause");
	return 0;
}