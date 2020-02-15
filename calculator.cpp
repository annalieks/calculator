//calculator.cpp : contains Calculator functions

#include "Calculator.h"
bool isoper(char op);
double sum(double val1, double val2);
double substact(double val1, double val2);
double multiply(double val1, double val2);
double divide(double val1, double val2);

//evaluates the given expression
double Calculator::evaluate()
{
	double result = 0.0;

	try {
		process_str();

		//after processing all expression
		while (!opers.empty())
			apply_oper();

		//add evaluated value to results queue
		add_to_queue(values.top());
		result = values.top();
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << "\n";
	}

	return result;
}

double Calculator::apply_binary_oper(double lval, double rval, char oper)
{
	double result = 0.0;

	switch (oper)
	{
	case '+': result = sum(lval, rval);
		break;
	case '-': result = substact(lval, rval);
		break;
	case '*': result = multiply(lval, rval);
		break;
	case '/': result = divide(lval, rval);
		break;
	default:
		break;
	}

	return result;
}

//get previous result from results queue
double Calculator::get_prevres(int arg)
{
	double result = 0.0;

	try
	{
		result = results.at(arg);
	}
	catch (std::out_of_range)
	{
		std::cout << "No result with such number ";
	}

	return result;
}

void Calculator::process_str()
{
	size_t i;
	//remove spaces from string
	expr.erase(remove_if(expr.begin(), expr.end(), isspace), expr.end());
	//add two symbols to avoid out of range errors
	expr = '[' + expr + ']';
	for (i = 1; i < expr.length() - 1; ++i)
	{
		if (isdigit(expr[i]) || expr[i] == '.')
			process_num(i);
		else if (isoper(expr[i]))
			process_oper(i);
		else
			input_error();
	}
}

// if correct operator, push into operators stack
void Calculator::process_oper(size_t& i)
{
	if (!is_unary(i))
	{
		while (!opers.empty() && get_precedence(opers.top())
			>= get_precedence(expr[i]))
			apply_oper();
		opers.push(expr[i]);
	}
}

// if correct number, push into values stack
void Calculator::process_num(size_t& i)
{
	double val;
	// if there's unary operator before number, apply it
	if (is_unary(i - 1))
	{
		size_t num = i - 1;
		val = apply_un_oper(extract_number(expr, i), expr[num]);
	}
	else
		val = extract_number(expr, i);
	values.push(val);
}

// apply operator and push calculated value to the values stack
void Calculator::apply_oper()
{
	double rval = values.top();
	values.pop();
	double lval = values.top();
	values.pop();
	char op = opers.top();
	opers.pop();
	values.push(apply_binary_oper(lval, rval, op));
}

// get operator precedence
int Calculator::get_precedence(char op)
{
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	return 3;
}

// extract number from string
double Calculator::extract_number(const std::string& expr, size_t& i)
{
	double num = 0, frac_part = 0;
	int dot_count = 0; // amount of dots in number
	while (i < expr.length()-1 && (isdigit(expr[i]) || expr[i] == '.'))
	{
		if (expr[i] == '.')
		{
			dot_count++;
			i++;
		}
		if (dot_count == 0)
		{
			while (i < expr.length() - 1 && isdigit(expr[i]))
				num = num * 10 + (expr[i++] - '0');
		}
		else if (dot_count == 1)
		{
			int dec_place = 1; // decimal place of number
			while (i < expr.length() - 1 && isdigit(expr[i]))
				frac_part += (expr[i++] - '0')/pow(10, dec_place++);
		}
		else if(dot_count > 1)
			input_error();
	}
	i--;
	return num + frac_part;
}

// check if symbol is allowed operator
bool isoper(char op)
{
	return (op == '+' || op == '-'
		|| op == '/' || op == '*'
		|| op == '$');
}

// check if operator is unary
bool Calculator::is_unary(size_t i)
{
	// the last element is operator
	// or string contains operator only
	if ((i == expr.length() - 2)
		|| (i == 1 && expr.length() <= 3))
		Calculator::input_error();

	// true if operator is first element and has a digit after
	else if (i == 1 && expr.length() > 3)
	{
		if (isdigit(expr[i + 1]))
			return true;
		else
			Calculator::input_error();
	}
	else if (expr[i] == '[')
		return false;

	// true if there is an operator before and a digit after
	else
		return (isoper(expr[i - 1]) && isdigit(expr[i + 1]));

	return false;
}

// apply unary operator to number and return number value
double Calculator::apply_un_oper(double val, char op)
{
	switch (op)
	{
	case '-': return (-val);
	case '+': return (val);
	case '$':
		if(val < 10)
			return get_prevres(int(val));
		input_error();
	default: input_error();
	}

	return 0.0;
}

// add calculated value to the front of results queue
void Calculator::add_to_queue(double val)
{
	if(results.size() > 9)
		results.pop_back();
	results.push_front(values.top());
}

//simple binary operations
double sum(double val1, double val2)
{
	return val1 + val2;
}
double substact(double val1, double val2)
{
	return val1 - val2;
}
double multiply(double val1, double val2)
{
	return val1 * val2;
}
double divide(double val1, double val2)
{
	return val1 / val2;
}