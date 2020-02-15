//main.cpp

#include "Calculator.h"
using namespace std;

int main()
{
	string expr;
	Calculator calc;
	while(true)
	{
		getline(cin >> ws, expr);
		calc.set_expr(expr);
		cout << calc.evaluate() << endl;
	}
	return 0;
}