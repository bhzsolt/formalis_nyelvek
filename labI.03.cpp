// Bodoki-Halmen Zsolt
// bzim1700, 531/1
//
// labI/3

#include <iostream>
#include <fstream>
#include <cstdio>
#include "automaton.hpp"

int main(int argc, const char *argv[])
{
	if (argc < 3) {
		std::cerr << "bad argument count" << std::endl;
		std::cerr << "usage: " << argv[0] << " automaton words" << std::endl;
		return 1;
	}

	try {
		Automaton automaton(argv[1]);
		std::ifstream input(argv[2]);
		std::ofstream output("labI.03.out");

		automaton.exclude_unreachable();
		automaton.exclude_useless();
		
		char buffer[256];
		input.getline(buffer, 256);
		do {
			output << buffer << ":\t" << (automaton.recognize(buffer) ? "true" : "false") << std::endl;
			input.getline(buffer, 256);
		} while (!input.eof());
		input.close();
		output.close();
	}
	catch (const char *exception) {
		std::cerr << exception << std::endl;
	}
	return 0;
}
