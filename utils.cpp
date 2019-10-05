#include "utils.hpp"
#include <cstring>

std::vector<char *> split(char *string, const char *delimiter)
{
	std::vector<char *> tokens;
	char *token = std::strtok(string, delimiter);
	while (token != nullptr) {
		tokens.push_back(token);
		token = std::strtok(nullptr, delimiter);
	}

	return tokens;
}
