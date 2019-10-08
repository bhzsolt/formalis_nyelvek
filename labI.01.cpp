//Bodoki-Halmen Zsolt
//bzim1700, 531/1
//
//labI/1

#include <iostream>
#include <fstream>
#include <cstdio>
#include "automaton.hpp"

#define BREAK()	{std::cout << "───────────────────────────" << std::endl;}

int main(int argc, const char *argv[])
{
	if (argc < 2) {
		std::cerr << "bad argument count" << std::endl;
		std::cerr << "usage: " << argv[0] << " automaton" << std::endl;
		return 1;
	}

	try {
		Automaton automaton(argv[1]);

		automaton.exclude_unreachable();
		std::ofstream out("labI.01.a.out");
		out << automaton;
		out.close();

		automaton.exclude_useless();
		out.open("labI.01.b.out");
		out << automaton;
		out.close();
	}
	catch (const char *exception) {
		std::cerr << exception << std::endl;
	}
	return 0;
}
