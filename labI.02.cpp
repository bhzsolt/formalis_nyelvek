//Bodoki-Halmen Zsolt
//bzim1700, 531/1
//
//labI/2

#include <iostream>
#include <fstream>
#include <cstdio>
#include "automaton.hpp"

int main(int argc, const char *argv[])
{
	if (argc < 3) {
		std::cerr << "bad argument count" << std::endl;
		std::cerr << "usage: " << argv[0] << " automaton1 automaton2" << std::endl;
		return 1;
	}

	try {
		Automaton automaton1(argv[1]);
		Automaton automaton2(argv[2]);

		std::cout << "input 1 == input 2: " << (automaton1 == automaton2 ? "true" : "false") << std::endl;
	}
	catch (const char *exception) {
		std::cerr << exception << std::endl;
	}
	return 0;
}
