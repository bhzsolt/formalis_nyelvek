//Bodoki-Halmen Zsolt
//bzim1700, 531/1
//
//labI/5

#include <iostream>
#include <fstream>
#include <cstdio>
#include "automaton.hpp"

#define BREAK()	{std::cout << "───────────────────────────" << std::endl;}

int main(int argc, const char *argv[])
{
	if (argc < 3) {
		std::cerr << "bad argument count" << std::endl;
		std::cerr << "usage: " << argv[0] << " automaton config.gv" << std::endl;
		return 1;
	}

	try {
		Automaton automaton(argv[1]);

		char buffer[256];
		sprintf(buffer, "%s.gv", argv[1]);
		automaton.print_dot(argv[2], buffer);
	}
	catch (const char *exception) {
		std::cerr << exception << std::endl;
	}
	return 0;
}
