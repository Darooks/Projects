#include <iostream>
#include <string>
#include <vector>
#include <sstream> 

using namespace std;

void convert(char polecenie[])
{
	vector <string> zmienne;
	vector <string> znaki;
	vector <string> prawdziwe_znaki;

	for (int i = 0; i < strlen(polecenie); i++)
	{
		if (polecenie[i] == 't' || polecenie[i] == 'f')
		{
			stringstream ss;
			string temp_str;
			char temp = polecenie[i];
			ss << temp;
			ss >> temp_str;
			
			zmienne.push_back(temp_str);
		}
		else if (polecenie[i] == 'K' || polecenie[i] == 'A')
		{
			stringstream ss;
			string temp_str;
			char temp = polecenie[i];
			ss << temp;
			ss >> temp_str;
			znaki.push_back(temp_str);
		}
		else if (polecenie[i] == 'N')
		{
			stringstream ss;
			string temp_str;
			char temp = polecenie[i];
			ss << temp;
			ss >> temp_str;
			znaki.push_back(temp_str);
		}
	}
	
	for (int i = 0; i < zmienne.size(); i++)
		cout << zmienne[i];
	for (int i = znaki.size() - 1; i >= 0; i--)
		cout << znaki[i];
	cout << endl;
	znaki.clear();
	zmienne.clear();
}

int main()
{
	int size;
	char polecenie[100];
//	char prefix[100];

	cin >> size;
	for (int i = 0; i < size; i++)
	{
		cin >> polecenie;

		convert(polecenie);
	}

	//system("pause");
	return 0;
}