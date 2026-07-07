#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <climits>

class Utils {
public:

	enum VECTOR_OUTPUT_STATES
	{
		PRE_CLEANUP,
		POST_CLEANUP
	};

	enum DEBUG_INDENTATION
	{
		INCREASE_INDENT,
		DECREASE_INDENT
	};

	Utils();
	~Utils();

	inline bool getDebug() const { return debug; }
	void setDebug();

	void debugOutput(std::string msg);

	void changeIndentation(DEBUG_INDENTATION INDENT);

	void debugOutput(std::string msg, int index);
	
	void debugOutput(std::string msg, double result);

	void debugVectorOutput(std::vector<std::string>& token);

	void debugVectorOutput(std::vector<std::string>& token, VECTOR_OUTPUT_STATES state);

	std::vector<std::string> cleanup(std::vector<std::string>& token, int& index, double& result, bool isSquareRoot);

	void clearCin() { std::cin.clear(); std::cin.ignore(INT_MAX, '\n'); }

	std::vector<std::string> cleanupParantheses(std::vector<std::string>& token, double& result, int& start, int& end);

private:
	bool debug = false;
	int indent = 0;
};