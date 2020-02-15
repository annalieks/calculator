#pragma once
#include <string>
#include <queue>
#include <stack>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <algorithm>

class Calculator
{
public:
	double evaluate();
	void set_expr(std::string str) { expr = str; }
	
private:
	std::string expr;
	std::deque<double> results;
	std::stack<double> values;
	std::stack<char> opers;

	int get_precedence(char);
	double get_prevres(int);
	
	double apply_un_oper(double, char);
	double apply_binary_oper(double, double, char);
	double extract_number(const std::string& expr, size_t& i);

	bool is_unary(size_t);

	void add_to_queue(double elem);
	void apply_oper();
	void process_str();
	void process_num(size_t&);
	void process_oper(size_t&);
	void input_error()
	{
		throw std::invalid_argument("Calculation error");
	}
};
