#pragma once

#include <string>
#include <unordered_set>
#include <vector>
#include <unordered_map>

class Calculator {
public:
	Calculator();
	~Calculator();

	void setDebug();
	bool getDebug() const;

	void Menu();

	double evaluateInput(const std::string& input);

private:

	bool validateInput(const std::string& input);

	bool validateInput(const std::vector<std::string>& input);

	std::vector<std::string> tokenize(const std::string& input);

	double loopProblem(std::vector<std::string>& token);

	std::vector<std::string> calculatePower(std::vector<std::string>& token, int& index);

	std::vector<std::string> squareRoot(std::vector<std::string>& token, int& index);

	std::vector<std::string> sin(std::vector<std::string>& token, int& index);

	std::vector<std::string> cos(std::vector<std::string>& token, int& index);

	std::vector<std::string> divide(std::vector<std::string>& token, int& index);

	std::vector<std::string> multiply(std::vector<std::string>& token, int& index);

	double addAndSubtract(std::vector<std::string>& token);

	std::vector<std::string> evaluateParantheses(std::vector<std::string>& token);


	int currentIndex = 0;
	const std::unordered_set<char> OPERATORS_BASIC = { '+', '-', '/', '*', '^'};
	const std::unordered_set<std::string> OPERATORS_ADVANCED = { "s", "sin", "cos"}; // finally used yippie
	std::unordered_map<char, int> parantheseCounts{ {'(', 0}, {')', 0} };
};