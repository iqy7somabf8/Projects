#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <climits>

class Utils {
public:

	Utils();
	~Utils();

	inline bool getDebug() const { return debug; }
	void setDebug();

	void debugOutput(std::string msg, int index, double result);

	void debugVectorOutput(std::vector<std::string>& token, bool preCleanup);

	std::vector<std::string> cleanup(std::vector<std::string>& token, int& index, double& result, bool isSquareRoot);

	void clearCin() { std::cin.clear(); std::cin.ignore(INT_MAX, '\n'); }

private:
	bool debug = false;
};