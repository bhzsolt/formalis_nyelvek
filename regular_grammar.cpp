#include "regular_grammar.hpp"
#include "utils.hpp"
#include <fstream>
#include <cstring>
#include <vector>

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

std::istream &RegularGrammar::read(std::istream &in)
{
	char buffer[256];
	std::vector<char *> tokens;

	in.getline(buffer, 256);
	tokens = split(buffer, " ");
	for (auto token : tokens) {
		char *tmp = new char [std::strlen(token)+1];
		tmp = std::strcpy(tmp, token);
		nonterminal.push_back(tmp);
	}

	in.getline(buffer, 256);
	tokens = split(buffer, " ");
	for (auto token : tokens) {
		char *tmp = new char [std::strlen(token)+1];
		tmp = std::strcpy(tmp, token);
		terminal.push_back(tmp);
	}

	in.getline(buffer, 256);
	start_symbol = 0;
	while (start_symbol < nonterminal.size() && 
			std::strcmp(buffer, nonterminal[start_symbol])) {
		++start_symbol;
	}
	if (start_symbol == nonterminal.size()) {
		throw "start symbol not a nonterminal symbol!\n";
	}

	in.getline(buffer, 256);
	do {
		tokens = split(buffer, " ");

		std::vector<int> tmp;
		int index = 0;
		while (index < nonterminal.size() && 
				std::strcmp(nonterminal[index], tokens[0])) {
			++index;
		}
		if (index == nonterminal.size()) {
			throw "symbol not nonterminal\n";
		}
		tmp.push_back(index);

		index = 0;
		while (index < terminal.size() &&
				std::strcmp(terminal[index], tokens[1])) {
			++index;
		}
		if (index == terminal.size()) {
			throw "symbol not terminal\n";
		}
		tmp.push_back(index);
		
		if (tokens.size() == 3) {
			index = 0;
			while (index < nonterminal.size() && 
					std::strcmp(nonterminal[index], tokens[0])) {
				++index;
			}
			if (index == nonterminal.size()) {
				throw "symbol not nonterminal\n";
			}
			tmp.push_back(index);
		}
		rules.push_back(tmp);
		in.getline(buffer, 256);
	} while (!in.eof());
	return in;
}

std::ostream &RegularGrammar::print(std::ostream &out)
{
	if (nonterminal.size()) {
		out << nonterminal[0];
		for (auto token : nonterminal) {
			out << " " << token;
		}
	}
	out << std::endl;

	if (terminal.size()) {
		out << terminal[0];
		for (auto token : terminal) {
			out << " " << token;
		}
	}
	out << std::endl;

	if (start_symbol < nonterminal.size()) {
		out << nonterminal[start_symbol];
	}
	out << std::endl;

	for (auto row : rules) {
		out << nonterminal[row[0]] << " " << terminal[row[1]];
		if (row.size() == 3) {
			out << " " << nonterminal[row[2]];
		}
		out << std::endl;
	}
	return out;
}
