#include "Utils.h"

Utils::Utils() = default;

Utils::~Utils() = default;

void Utils::setDebug() { debug = (debug ? false : true); }

void Utils::debugOutput(std::string msg, int index)
{
	if (debug)
	{
		for (int i = 0; i < indent; ++i) std::cout << "\t";
		std::cout << msg << index << "\n\n";
	}
}

void Utils::debugOutput(std::string msg, double result)
{
	if (debug)
	{
		for (int i = 0; i < indent; ++i) std::cout << "\t";
		std::cout << msg << result << "\n\n";
	}
}

void Utils::debugOutput(std::string msg)
{
	if (debug)
	{
		for (int i = 0; i < indent; ++i) std::cout << "\t";
		std::cout << msg << "\n\n";
	}
}

void Utils::changeIndentation(DEBUG_INDENTATION INDENT)
{
	switch (INDENT)
	{
	case INCREASE_INDENT:
		++indent;
		break;
	case DECREASE_INDENT:
		--indent;
		break;
	}
}

void Utils::debugVectorOutput(std::vector<std::string>& token)
{
	if (debug) {
		for (int i = 0; i < indent; ++i) std::cout << "\t";
		for (const auto& c : token) std::cout << c << ", ";
		std::cout << "\n\n";
	}
}

void Utils::debugVectorOutput(std::vector<std::string>& token, VECTOR_OUTPUT_STATES state)
{
	if (debug) {
		for (int i = 0; i < indent; ++i) std::cout << "\t";
		switch (state)
		{
		case PRE_CLEANUP:
			std::cout << "Pre cleanup:\n";
			break;
		case POST_CLEANUP:
			std::cout << "Post cleanup:\n";
			break;
		default:
			std::cout << "What the fuck did you put in for this to display???\n";
		}
		for (int i = 0; i < indent; ++i) std::cout << "\t";
		for (const auto& c : token) std::cout << c << ", ";
		std::cout << "\n\n";
	}
}

std::vector<std::string> Utils::cleanup(std::vector<std::string>& token, int& index, double& result, bool isSquareRoot)
{
	token[index - (isSquareRoot ? 0 : 1)] = std::to_string(result);
	debugVectorOutput(token, PRE_CLEANUP);
	token.erase(token.begin() + index + (isSquareRoot ? 1 : 0), token.begin() + index + 2);
	--index;
	debugVectorOutput(token, POST_CLEANUP);

	this->changeIndentation(Utils::DECREASE_INDENT);

	return token;
}

std::vector<std::string> Utils::cleanupParantheses(std::vector<std::string>& token, double& result, int& start, int& end)
{
	token[start - 1] = std::to_string(result);
	debugVectorOutput(token, PRE_CLEANUP);
	token.erase(token.begin() + start, token.begin() + end + 1);
	debugVectorOutput(token, POST_CLEANUP);
	return token;
}
	