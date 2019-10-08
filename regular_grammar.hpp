#pragma once
#include <iostream>
#include <vector>

#include "automaton.hpp"

class RegularGrammar {
	private:
		std::vector<char *> nonterminal;
		std::vector<char *> terminal;
		int start_symbol;
		std::vector<std::vector<int>> rules;

	public:
		std::istream &read(std::istream &);
		std::ostream &print(std::ostream &) const;

		RegularGrammar() {};
		RegularGrammar(const char *);
		RegularGrammar(const RegularGrammar &);
		~RegularGrammar();

};

std::istream &operator >>(std::istream &, RegularGrammar &);
std::ostream &operator <<(std::ostream &, const RegularGrammar &);
