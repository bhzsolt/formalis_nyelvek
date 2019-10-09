// Bodoki-Halmen Zsolt
// bzim1700, 531/1

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include "automaton.hpp"
#include "regular_grammar.hpp"

#define BREAK()	{std::cout << "───────────────────────────" << std::endl;}

int main(int argc, const char *argv[])
{
	if (argc < 3) {
		std::cerr << "bad argument count" << std::endl;
		std::cerr << "usage: " << argv[0] << " regular_grammar config.gv" << std::endl;
		return 1;
	}
	try {
		RegularGrammar grammar;

		std::ifstream input(argv[1]);
		input >> grammar;
		input.close();

		std::cout << grammar;

		char buffer[256];
		Automaton automaton = grammar.to_automaton();
		sprintf(buffer, "%s.gv", argv[1]);
		automaton.print_dot(argv[2], buffer);

		sprintf(buffer, "dot -Txlib %s.gv", argv[1]);
		system(buffer);
	}
	catch (const char *exception) {
		std::cerr << exception << std::endl;
	}
	return 0;
}
