#include <iostream>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	stack<char> calcStack;
	char input;

	while (true)
	{
		cin >> input;

		char num;

		if (input == 't' || input == 'f')
		{
			num = input;
			calcStack.push(num);
		}
		else if (input == 'K' || input == 'A' || input == 'N')
		{

		}
	}

	system("pause");
	return 0;
}