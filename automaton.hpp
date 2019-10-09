#pragma once
#include <iostream>
#include <vector>

class Automaton {
		friend class RegularGrammar;
	private:
		int size;
		std::vector<int> si;
		std::vector<int> ei;
		std::vector<char *> labels;
		std::vector<char *> letters;
		int **graph;
		bool recognize_helper(int, const char *) const;
	public:
		Automaton();
		Automaton(const char *);
		Automaton(const Automaton &);
		~Automaton();

		std::istream &read(std::istream &);
		std::ostream &print_test(std::ostream &) const;
		std::ostream &print(std::ostream &) const;
		
		void exclude_unreachable();
		Automaton exclude_unreachable2() const;
		void exclude_useless();
		Automaton exclude_useless2() const;

		bool operator ==(const Automaton &) const;

		bool recognize(const char *) const;
		void from_regexp(const char *);

		void print_dot(const char *, const char *) const;
};

std::istream &operator >>(std::istream &, Automaton &);
std::ostream &operator <<(std::ostream &, const Automaton &);
