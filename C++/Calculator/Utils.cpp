#include "Utils.h"

Utils::Utils() = default;

Utils::~Utils() = default;

void Utils::setDebug()
{
	debug = (debug ? false : true);
}

void Utils::debugOutput(std::string msg, int index, double result)
{
	if (debug && index != -1) std::cout << msg << index << "\n";
	else if (debug && result != -1)std::cout << msg << result << "\n";
	else if (debug) std::cout << msg << "\n";
}

void Utils::debugVectorOutput(std::vector<std::string>& token, bool preCleanup)
{
	if (debug) {
		std::cout << (preCleanup ? "Pre Cleanup: \n" : "Post Cleanup: \n");
		for (std::string c : token) std::cout << c << ", ";
		std::cout << "\n";
	}
}

std::vector<std::string> Utils::cleanup(std::vector<std::string>& token, int& index, double& result, bool isSquareRoot)
{
	token[index - (isSquareRoot ? 0 : 1)] = std::to_string(result);
	debugVectorOutput(token, true);
	token.erase(token.begin() + index + (isSquareRoot ? 1 : 0), token.begin() + index + 2);
	--index;
	debugVectorOutput(token, false);
	return token;
}

