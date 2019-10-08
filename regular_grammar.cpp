#include "regular_grammar.hpp"
#include "utils.hpp"
#include <fstream>
#include <cstring>

RegularGrammar::RegularGrammar(const char *filename)
{
	std::ifstream input(filename);
	read(input);
	input.close();
}

RegularGrammar::RegularGrammar(const RegularGrammar &cpy) : start_symbol(cpy.start_symbol), 
															rules(cpy.rules)
{
	for (auto string : cpy.nonterminal) {
		char *tmp = new char[std::strlen(string)+1];
		tmp = std::strcpy(tmp, string);
		nonterminal.push_back(tmp);
	}

	for (auto string : cpy.terminal) {
		char *tmp = new char[std::strlen(string)+1];
		tmp = std::strcpy(tmp, string);
		terminal.push_back(tmp);
	}
}

RegularGrammar::~RegularGrammar()
{
	for (auto string : nonterminal) {
		delete string;
	}
	for (auto string : terminal) {
		delete string;
	}
}

std::istream &operator >>(std::istream &in, RegularGrammar &grammar)
{
	return grammar.read(in);
}

std::ostream &operator <<(std::ostream &out, const RegularGrammar &grammar)
{
	return grammar.print(out);
}


