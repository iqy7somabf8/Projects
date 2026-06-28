#include "Calculator.h"

#include <iostream>
#include <cctype>
#include <vector>
#include <unordered_map>

#include "Utils.h"

Utils utils;

Calculator::Calculator() = default;
Calculator::~Calculator() = default;

void Calculator::setDebug() { utils.setDebug(); }
bool Calculator::getDebug() const { return utils.getDebug(); }

double Calculator::sqrt(int number)
{
	double result = 1;
	for (int i = 0; i < 99; i++) result = (result + number / result) / 2;
	return result;
}
	/*if (number == 1 || number == 0) return number;

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

	return r; 
	*/

	// Only able to return integers.
	// Sadly has to be replaced by an inferior algorithm that takes around 99 tried to guesstimate the square root

//In-order executed methods // not anymore tho its kinda fucked
void Calculator::Menu() {
	std::cout << "Calculator\n"
	<< "|1. Help\n"
	<< "|2. Debug >> currently " << (utils.getDebug() ? "Enabled\n" : "Disabled\n")
	<< "|To exit type 'end'\n"
	<< ">>";
}

bool Calculator::validateInput(const std::string& input)
{
	std::unordered_map<char, int> paranthesesCounts = { {'(', 0}, { ')', 0 } };

	if (input.empty()) return false;

	if (OPERATORS.find(input.front()) != OPERATORS.end() && input[0] != 's' || OPERATORS.find(input.back()) != OPERATORS.end()) return false;

	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == 's' && (isdigit(input[i + 1] && std::stoi(std::to_string(input[i+1])) < 1))) { std::cout << "Finding the square root of a negative number is impossible.\n"; return false; }

		if (input[i] == '(' || input[i] == ')') paranthesesCounts[input[i]]++;
	}

	utils.debugOutput("Parantheses counts: ['(: " + std::to_string(paranthesesCounts['(']) + "'] ['): " + std::to_string(paranthesesCounts[')']) + "']"); // so cute of me to immitate the readability c-library code
	if (paranthesesCounts['('] != paranthesesCounts[')']) { std::cout << "Mismatched parantheses\n"; return false; }

	return true;
}

std::vector<std::string> Calculator::evaluateParantheses(std::vector<std::string>& token)
{

	utils.debugOutput("Parantheses Evaluation Invoked");

	std::vector<std::string> parantheseToken = {};
	int offset = 0;

	for (int i = 0; i < token.size(); ++i)
	{

		if (i > token.size() - offset) break;

		if (token[i] == "(")
		{
			try { // Check if theres a number before the paranthese. If so, adds a '*' operator.
				if (std::stoi(token[i - 1]) + 1) token.insert(token.begin() + i, "*");
				utils.debugOutput("Added '*' operator at index: ", i);
				i++;
			} catch (...) {
				utils.debugOutput("Exception caught"); // TODO: make this more clear on what it means.
			}

			int start = i + 1;
			int end = 0;

			for (int j = start; j < token.size(); j++)
			{
				parantheseToken.push_back(token[j]);

				if (token[j] == ")") { end = j; break; }
			}
			parantheseToken.pop_back();

			double result = loopProblem(parantheseToken);
			token = utils.cleanupParantheses(token, result, start, end);
			offset += end - start + 1;
		}
	}
	
	utils.debugOutput("Parantheses Evaluation Finished");

	return token;
}

double Calculator::evaluateInput(const std::string& input) 
{
	if (validateInput(input))
	{
		std::vector<std::string> token = tokenize(input);
		token = this->evaluateParantheses(token);
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

		else if (OPERATORS.find(c) != OPERATORS.end() || (c == '(' || c == ')'))
		{
			if (!currentNum.empty())
			{
				token.push_back(currentNum);
				currentNum = "";
			}
			token.push_back(std::string(1, c));
		}
	}

	if (!currentNum.empty()) token.push_back(currentNum);

	return token;
}

double Calculator::loopProblem(std::vector<std::string>& token) 
{
	for (int i = 0; i < token.size(); i++)
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
	utils.debugOutput("Power of Calculation");
	double result = 1;
	double base = std::stod(token[index - 1]);
	double exponent = std::stod(token[index + 1]);
	for (int i = 0; i < exponent; i++) result *= base;
	utils.debugOutput("Power inbetween result: ", result);
	return utils.cleanup(token, index, result, false);
}

std::vector<std::string> Calculator::squareRoot(std::vector<std::string>& token, int& index)
{
	utils.debugOutput("Square Root Calculation");
	int squareNumber = std::stoi(token[index + 1]);
	double result = sqrt(squareNumber);
	utils.debugOutput("Inbetween result: ", result);
	utils.debugOutput("Index: ", index);
	return utils.cleanup(token, index, result, true);
}

std::vector<std::string> Calculator::divide(std::vector<std::string>& token, int& index)
{
	utils.debugOutput("Division");
	double result = std::stod(token[index - 1]) / std::stod(token[index + 1]);
	utils.debugOutput("Inbetween result: ", result);
	utils.debugOutput("Index: ", index);
	return utils.cleanup(token, index, result, false);
}

std::vector<std::string> Calculator::multiply(std::vector<std::string>& token, int& index) 
{
	utils.debugOutput("Multiplication");
	double result = std::stod(token[index - 1]) * std::stod(token[index + 1]);
	utils.debugOutput("Inbetween result: ", result);
	utils.debugOutput("Index: ", index);
	return  utils.cleanup(token, index, result, false);
}

double Calculator::addAndSubtract(std::vector<std::string>& token) 
{
	utils.debugOutput("Addition and Subtraction");
	double result = std::stod(token[0]);
	if (token.size() > 1)
	{
		result = std::stod(token[0]);
		for (int i = 1; i < token.size(); i += 2)
		{
			char op = token[i][0];
			double num = std::stod(token[i + 1]);

			if (op == '+') result += num;
			else if (op == '-') result -= num;
		}
	}
	return result;
}