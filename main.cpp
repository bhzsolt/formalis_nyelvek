#include <iostream>
#include <fstream>
#include "automaton.hpp"

#define BREAK()	{std::cout << "───────────────────────────" << std::endl}

int main(int argc, const char *argv[])
{
	if (argc < 2) {
		std::cerr << "bad argument count" << std::endl;
		return 1;
	}

	try {
		Automaton automaton1(argv[1]);
		Automaton automaton2(argv[2]);

		std::ofstream out1("01.out");
		automaton1.exclude_unreachable();
		automaton1.exclude_useless();
		out1 << automaton1;
		out1.close();

		std::cout << (automaton1 == automaton2 ? "true" : "false") << std::endl;
		BREAK();
		automaton1.print_test(std::cout);
		BREAK();
		std::cout << "c:\t" << (automaton1.recognize("c") ? "true" : "false") << std::endl;
		std::cout << "aba:\t" << (automaton1.recognize("aba") ? "true" : "false") << std::endl;
		std::cout << "abab:\t" << (automaton1.recognize("abab") ? "true" : "false") << std::endl;
		std::cout << "a:\t" << (automaton1.recognize("a") ? "true" : "false") << std::endl;
		std::cout << "abb:\t" << (automaton1.recognize("abb") ? "true" : "false") << std::endl;
		std::cout << "aaab:\t" << (automaton1.recognize("aaab") ? "true" : "false") << std::endl;
		std::cout << "aab:\t" << (automaton1.recognize("aab") ? "true" : "false") << std::endl;
		std::cout << "bb:\t" << (automaton1.recognize("bb") ? "true" : "false") << std::endl;
		std::cout << "abaaab:\t" << (automaton1.recognize("abaaab") ? "true" : "false") << std::endl;
		std::cout << "abcba:\t" << (automaton1.recognize("abcba") ? "true" : "false") << std::endl;
	}
	catch (const char *exception) {
		std::cerr << exception << std::endl;
	}
	return 0;
}
