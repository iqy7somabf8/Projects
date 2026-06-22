#include "Calculator.h"

#include <iostream>
#include <cmath>
#include <cctype>
#include <vector>

#include "Utils.h"

Utils utils;

Calculator::Calculator() = default;
Calculator::~Calculator() = default;

void Calculator::setDebug() { utils.setDebug(); }
bool Calculator::getDebug() const { return utils.getDebug(); }

double Calculator::sqrt(int number)
{
	if (number == 1 || number == 0) return number;

	int l = 1;
	int r = number;

	while (l <= r)
	{

	int m = l + (r - l) / 2;

	long long square = (long long)m * m;

	if (square > number) r = m - 1;
	else if (square == number) return m;
	else l = m + 1;
	}

	return (double)std::round(r); // W leetcode
}

//In-order executed methods
void Calculator::Menu() {
	std::cout << "Calculator\n"
	<< "|1. Help\n"
	<< "|2. Debug >> currently " << (utils.getDebug() ? "Enabled\n" : "Disabled\n")
	<< "|To exit type 'end'\n"
	<< ">>";
}

bool Calculator::validateInput(const std::string& input)
{
	if (input.empty()) return false;

	if (OPERATORS.find(input.front()) != OPERATORS.end() && input[0] != 's' || OPERATORS.find(input.back()) != OPERATORS.end()) return false;

	for (int i = 0; i < input.size() - 1; i++) 
	{
		if (input[i] == 's' && std::stoi(input.substr(i + 1)) < 1) { std::cout << "Finding the square root of a negative number is impossible.\n"; return false; }
	}
	return true;
}

double Calculator::evaluateInput(const std::string& input) 
{
	if (validateInput(input))
	{
		std::vector<std::string> token = tokenize(input);
		return loopProblem(token);
	}

	std::cout << "Encountered error whilst validating input. Try again.\n";
	utils.clearCin();
	return false;
}

//tokenize the input all into one vector
std::vector<std::string> Calculator::tokenize(const std::string& input) 
{
	std::vector<std::string> token;
	std::string currentNum = "";

	for (char c : input)
	{
		if (isdigit(c) || c == '.') currentNum += c;


		else if (OPERATORS.find(c) != OPERATORS.end())
		{
			if (!currentNum.empty())
			{
				token.push_back(currentNum);
				currentNum = "";
			}
			token.push_back(std::string(1, c));
		}
	}

	//Double check
	if (!currentNum.empty()) token.push_back(currentNum);
	return token;
}


double Calculator::loopProblem(std::vector<std::string>& token) 
{
	for (int i = 0; i < token.size() + 1; i++)
	{
		if (token[i] == "^") token = calculatePower(token, i);
		else if (token[i] == "s") token = squareRoot(token, i);
		else if (token[i] == "/") token = divide(token, i);
		else if (token[i] == "*") token = multiply(token, i);
	}
	return addAndSubtract(token);
}

std::vector<std::string> Calculator::calculatePower(std::vector<std::string>& token, int& index) 
{
	utils.debugOutput("Power of Calculation", -1, -1);
	double result = 1;
	double base = std::stod(token[index - 1]);
	double exponent = std::stod(token[index + 1]);
	while (exponent > 0)
	{
		--exponent;
		result *= base;
	}
	utils.debugOutput("Power inbetween result: ", -1, result);
	return utils.cleanup(token, index, result, false);
}

std::vector<std::string> Calculator::squareRoot(std::vector<std::string>& token, int& index)
{
	utils.debugOutput("Square Root Calculation", -1, -1);
	int squareNumber = std::stoi(token[index + 1]);
	double result = sqrt(squareNumber);
	utils.debugOutput("Inbetween result: ", -1, result);
	utils.debugOutput("Index: ", index, -1);
	return utils.cleanup(token, index, result, true);
}

std::vector<std::string> Calculator::divide(std::vector<std::string>& token, int& index)
{
	utils.debugOutput("Division", -1, -1);
	double result = std::stod(token[index - 1]) / std::stod(token[index + 1]);
	utils.debugOutput("Inbetween result: ", -1, result);
	utils.debugOutput("Index: ", index, -1);
	return utils.cleanup(token, index, result, false);
}

std::vector<std::string> Calculator::multiply(std::vector<std::string>& token, int& index) 
{
	utils.debugOutput("Multiplication", -1, -1);
	double result = std::stod(token[index - 1]) * std::stod(token[index + 1]);
	utils.debugOutput("Inbetween result: ", -1, result);
	utils.debugOutput("Index: ", index, -1);
	return  utils.cleanup(token, index, result, false);
}

double Calculator::addAndSubtract(std::vector<std::string>& token) 
{
	utils.debugOutput("Addition and Subtraction", -1, -1);
	double result = std::stod(token[0]);
	if (token.size() > 1)
	{
		result = std::stod(token[0]);
		for (std::size_t i = 1; i < token.size(); i += 2)
		{
			char op = token[i][0];
			double num = std::stod(token[i + 1]);

			if (op == '+') result += num;
			else if (op == '-') result -= num;
		}
	}
	return result;
}