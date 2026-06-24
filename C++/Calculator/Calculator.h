#pragma once

#include <string>
#include <unordered_set>
#include <vector>

class Calculator {
public:
	Calculator();
	~Calculator();

	void setDebug();
	bool getDebug() const;

	void Menu();

	double sqrt(int number);

	double evaluateInput(const std::string& input);

private:

	bool validateInput(const std::string& input);

	std::vector<std::string> tokenize(const std::string& input);

	double loopProblem(std::vector<std::string>& token);

	std::vector<std::string> calculatePower(std::vector<std::string>& token, int& index);

	std::vector<std::string> squareRoot(std::vector<std::string>& token, int& index);

	std::vector<std::string> divide(std::vector<std::string>& token, int& index);

	std::vector<std::string> multiply(std::vector<std::string>& token, int& index);

	double addAndSubtract(std::vector<std::string>& token);

	std::vector<std::string> evaluateParantheses(std::vector<std::string>& token);


	int currentIndex = 0;
	std::vector<std::string> token {};
	const std::unordered_set<char> OPERATORS = { '+', '-', '/', '*', '^', 's' };
	std::vector<std::vector<std::string>> parantheses {};
};