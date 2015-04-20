#include <iostream>
#include <stack>
using namespace std;

#define MAX 1000
#define LEFT_DONE '#'

bool isOperator(char ch) {
	return ch == 'K' || ch == 'A' || ch == 'N';
}

int main() {

	//e input expression and p output expression
	char e[MAX], p[MAX];
	stack<char> stk;
	int ile_razy;
	cin >> ile_razy;
	for (int o = 0; o < ile_razy; o++) {

		cin >> e;

		int j = 0;
		//until the end of expression riches
		for (int i = 0; e[i]; i++){

			//cout << e[i] << endl;
			if (isOperator(e[i])){
				stk.push(e[i]);
				//cout << "jestem" << endl;
			}
			else {
				p[j++] = e[i];
				//cout << "jestem" << e[i] << endl;
				while (!stk.empty() && stk.top() == LEFT_DONE){
					stk.pop();
					p[j++] = stk.top();

					stk.pop();
				}
				stk.push(LEFT_DONE);
			}
		}
		p[j] = 0;
		cout << p << endl;
		e[0] = NULL;
		p[0] = NULL;

	}

	//system("pause");
	return 0;
}
