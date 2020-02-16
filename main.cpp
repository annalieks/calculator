//main.cpp

#include "Calculator.h"
using namespace std;

int main()
{
	string expr;
	Calculator calc;
	while(true)
	{
	    cout << "Enter your expression: ";
		getline(cin >> ws, expr);
		calc.set_expr(expr);
		cout << "Your result: ";
		cout << calc.evaluate() << endl;
	}
	return 0;
}