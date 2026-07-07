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

//In-order executed methods
void Calculator::Menu() 
{
	std::cout << "Calculator\n"
	<< "|h. Help\n"
	<< "|d. Debug >> currently " << (utils.getDebug() ? "Enabled\n" : "Disabled\n")
	<< "|To exit type 'end'\n"
	<< ">>";
}

double Calculator::evaluateInput(const std::string& input) 
{
	if (validateInput(input))
	{
		std::vector<std::string> token = tokenize(input);
		token = evaluateParantheses(token);

		if (token.empty()); 
		// very spaghetti around here. if token is empty doesnt even get to second validation. if validation fails it just print the botton error message

		// Second check. For now just to make sure that we aren't trying to compute the square root of a negative number
		else if(validateInput(token)) return loopProblem(token);
	}
	std::cout << "Encountered error whilst validating input. Try again.\n";
	utils.clearCin();
	return -1.404;
}

bool Calculator::validateInput(const std::string& input)
{
	if (input.empty()) return false;

	// Check if there is an operator at the front or the back of the problem
	if (OPERATORS_BASIC.find(input.front()) != OPERATORS_BASIC.end() && input[0] != 's' || OPERATORS_BASIC.find(input.back()) != OPERATORS_BASIC.end()) return false;

	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '(' || input[i] == ')') parantheseCounts[input[i]]++;

		if (input[i] == 's' && input[i + 1] == '-') { std::cout << "Finding the square root of a negative number / 0 is impossible\n"; return false; }
	}

	utils.debugOutput("Parantheses counts: ['(: " + std::to_string(parantheseCounts['(']) + "'] ['): " + std::to_string(parantheseCounts[')']) + "']"); // so cute of me to immitate the readability of c-library code
	if (parantheseCounts['('] != parantheseCounts[')'])
	{
		std::cout << "Mismatched parantheses\n";
		parantheseCounts['('] = 0;
		parantheseCounts[')'] = 0;
		return false;
	}

	return true;
}

//tokenize the input all into one vector
std::vector<std::string> Calculator::tokenize(const std::string& input) 
{
	utils.debugOutput("Tokenization Invoked");
	utils.changeIndentation(Utils::INCREASE_INDENT);

	std::vector<std::string> token;
	std::string currentNum = "";
	std::string currentOp = "";

	for (const auto& c : input)
	{
		if (isdigit(c) || c == '.') currentNum += c;
		else if (isalpha(c)) currentOp += c;

		else if (OPERATORS_BASIC.find(c) != OPERATORS_BASIC.end() || (c == '(' || c == ')'))
		{
			if (!currentNum.empty())
			{
				token.push_back(currentNum);
				currentNum = "";
			}

			if (!currentOp.empty() && OPERATORS_ADVANCED.find(currentOp) == OPERATORS_ADVANCED.end())
			{
				
				std::cout << "Invalid Operator found\n";
				utils.clearCin();
				return {};
			}
			else if(!currentOp.empty())
			{
				token.push_back(currentOp);
				currentOp = "";
			}

			token.push_back(std::string(1, c));
		}
	}

	if (!currentNum.empty()) token.push_back(currentNum);
	if (!currentOp.empty() && OPERATORS_ADVANCED.find(currentOp) == OPERATORS_ADVANCED.end())
	{
		std::cout << "Invalid Operator found\n";
		utils.clearCin();
		return {};
	}
	else if (!currentOp.empty()) token.push_back(currentOp);

	utils.debugOutput("Tokens:");
	utils.debugVectorOutput(token);

	utils.changeIndentation(Utils::DECREASE_INDENT);
	utils.debugOutput("Tokenization Finished");

	return token;
}

std::vector<std::string> Calculator::evaluateParantheses(std::vector<std::string>& token)
{

	utils.debugOutput("Parantheses Evaluation Invoked");
	utils.changeIndentation(Utils::INCREASE_INDENT);

	int seenParantheses = 0;
	std::vector<std::string> parantheseToken = {};

	for (int i = 0; i < token.size(); ++i)
	{
		if (token[i] == "(" && ++seenParantheses == parantheseCounts['('])
		{
			try { // Check if theres a number before the paranthese. If so, adds a '*' operator.

				if (i == 0) utils.debugOutput("Paranthese at index 0");

				else if (std::stoi(token[i - 1]) + 1)
				{
					token.insert(token.begin() + i, "*");
					utils.debugOutput("Added '*' operator at index: ", i);
					utils.debugVectorOutput(token);
					i++;
				}

			}
			catch (...) { utils.debugOutput("Exception caught"); }// TODO: make this more clear on what it means.

			int start = i + 1;
			int end = 0;

			for (int j = start; j < token.size(); j++)
			{
				parantheseToken.push_back(token[j]);

				if (token[j] == ")")
				{
					end = j;
					try { // Check if theres a number after the paranthese. If so, adds a '*' operator.

						// bs check. The try statement shouldn't still require me to make sure j isn't the index of the last element :/
						if (j != token.size() - 1 && std::stoi(token[j + 1]) + 1)
						{
							token.insert(token.begin() + j + 1, "*");
							utils.debugOutput("Added '*' operator at index: ", j);
							utils.debugVectorOutput(token);
						}

					}
					catch (...) { utils.debugOutput("Exception caught"); }// TODO: make this more clear on what it means.
					break;
				}
			}

			parantheseToken.pop_back();
			double result = loopProblem(parantheseToken);
			parantheseToken.clear();

			token = utils.cleanupParantheses(token, result, start, end);

			i = -1; // also incredibly hacky way to restart the loop but nobody really gaf
			parantheseCounts['(']--;
			parantheseCounts[')']--;
			seenParantheses = 0; // very hacky but idk
		}
	}

	utils.changeIndentation(Utils::DECREASE_INDENT);
	utils.debugOutput("Parantheses Evaluation Finished");

	return token;
}

bool Calculator::validateInput(const std::vector<std::string>& input)
{
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == "s" && std::stoi(input[i + 1]) < 0) { std::cout << "Finding the square root of a negative number / 0 is impossible\n"; return false; }
	}
	return true;
}

double Calculator::loopProblem(std::vector<std::string>& token) 
{

	for (int i = 0; i < token.size(); i++)
	{
		if (token[i] == "^") token = calculatePower(token, i);
		else if (token[i] == "s") token = squareRoot(token, i);
		else if (token[i] == "sin") token = sin(token, i);
		else if (token[i] == "cos") token = cos(token, i);
	}
	// Literally no idea why my dumbass self didn't realise this would absolutely not work in a single loop smh
	for (int i = 0; i < token.size(); i++)
	{
		if (token[i] == "/") token = divide(token, i);
		else if (token[i] == "*") token = multiply(token, i);
	}
	return addAndSubtract(token);
}

std::vector<std::string> Calculator::calculatePower(std::vector<std::string>& token, int& index) 
{
	utils.debugOutput("Power of Calculation");
	utils.changeIndentation(Utils::INCREASE_INDENT);
	double result = 1;
	double base = std::stod(token[index - 1]);
	int exponent = std::stoi(token[index + 1]);
	for (int i = 0; i < exponent; i++) result *= base;
	utils.debugOutput("Power inbetween result: ", result);
	return utils.cleanup(token, index, result, false);
}

std::vector<std::string> Calculator::squareRoot(std::vector<std::string>& token, int& index)
{
	utils.debugOutput("Square Root Calculation");
	utils.changeIndentation(Utils::INCREASE_INDENT);
	double squareNumber = std::stod(token[index + 1]);
	double result = std::sqrt(squareNumber);
	utils.debugOutput("Inbetween result: ", result);
	utils.debugOutput("Index: ", index);
	return utils.cleanup(token, index, result, true);
}

std::vector<std::string> Calculator::sin(std::vector<std::string>& token, int& index)
{
	utils.debugOutput("Sin() Calculation");
	utils.changeIndentation(Utils::INCREASE_INDENT);
	double degree = std::stod(token[index + 1]);
	double result = std::sin(degree);
	utils.debugOutput("Inbetween result: ", result);
	utils.debugOutput("Index: ", index);
	return utils.cleanup(token, index, result, true);
}

std::vector<std::string> Calculator::cos(std::vector<std::string>& token, int& index)
{
	utils.debugOutput("Cos() Calculation");
	utils.changeIndentation(Utils::INCREASE_INDENT);
	double degree = std::stod(token[index + 1]);
	double result = std::cos(degree);
	utils.debugOutput("Inbetween result: ", result);
	utils.debugOutput("Index: ", index);
	return utils.cleanup(token, index, result, true);
}

std::vector<std::string> Calculator::divide(std::vector<std::string>& token, int& index)
{
	utils.debugOutput("Division");
	utils.changeIndentation(Utils::INCREASE_INDENT);
	double result = std::stod(token[index - 1]) / std::stod(token[index + 1]);
	utils.debugOutput("Inbetween result: ", result);
	utils.debugOutput("Index: ", index);
	return utils.cleanup(token, index, result, false);
}

std::vector<std::string> Calculator::multiply(std::vector<std::string>& token, int& index) 
{
	utils.debugOutput("Multiplication");
	utils.changeIndentation(Utils::INCREASE_INDENT);
	double result = std::stod(token[index - 1]) * std::stod(token[index + 1]);
	utils.debugOutput("Inbetween result: ", result);
	utils.debugOutput("Index: ", index);
	return  utils.cleanup(token, index, result, false);
}

double Calculator::addAndSubtract(std::vector<std::string>& token) 
{
	double result = std::stod(token[0]);
	if (token.size() > 1)
	{
		utils.debugOutput("Addition and Subtraction");
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