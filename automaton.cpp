#include <iomanip>
#include <fstream>
#include <vector>
#include <cstring>
#include <stack>
#include "automaton.hpp"

Automaton::Automaton()
{
	size = 0;
}

Automaton::~Automaton()
{
	for (int i = 0; i < labels.size(); ++i) {
		delete labels[i];
	}

	for (int i = 0; i < letters.size(); ++i) {
		delete letters[i];
	}

	for (int i = 0; i < size; ++i) {
		delete graph[i];
	}
	delete graph;
}

Automaton::Automaton(const char *filename)
{
	std::ifstream input(filename);
	if (!input.good()) {
		throw "bad file!\n";
	}
	read(input);
	input.close();
}

Automaton::Automaton(const Automaton &copy) : si(copy.si), ei(copy.ei), size(copy.size)
{
	for (int i = 0; i < copy.labels.size(); ++i) {
		char *tmp = new char[std::strlen(copy.labels[i])+1];
		tmp = std::strcpy(tmp, copy.labels[i]);
		labels.push_back(tmp);
	}
	for (int i = 0; i < copy.letters.size(); ++i) {
		char *tmp = new char[std::strlen(copy.letters[i])+1];
		tmp = std::strcpy(tmp, copy.letters[i]);
		letters.push_back(tmp);
	}
	graph = new int *[size];
	for (int i = 0; i < size; ++i) {
		graph[i] = new int[size];
		for (int j = 0; j < size; ++j) {
			graph[i][j] = copy.graph[i][j];
		}
	}
}

std::istream &Automaton::read(std::istream &in) 
{
	char buffer[256];
	
	in.getline(buffer, 256);
	char *token = std::strtok(buffer, " ");
	while (token != nullptr) {
		char *tmp = new char[std::strlen(token)+1];
		tmp = strcpy(tmp, token);
		labels.push_back(tmp);
		token = std::strtok(nullptr, " ");
	}

	size = labels.size();
	graph = new int *[size];
	for (int i = 0; i < size; ++i) {
		graph[i] = new int[size];
		for (int j = 0; j < size; ++j) {
			graph[i][j] = -1;
		}
	}
	
	in.getline(buffer, 256);
	token = std::strtok(buffer, " ");
	while (token != nullptr) {
		char *tmp = new char[std::strlen(token)+1];
		tmp = strcpy(tmp, token);
		letters.push_back(tmp);
		token = std::strtok(nullptr, " ");
	}

	in.getline(buffer, 256);
	token = std::strtok(buffer, " ");
	while (token != nullptr) {
		char *tmp = new char[std::strlen(token)+1];
		tmp = strcpy(tmp, token);
		int i = 0;
		bool found = false;
		while (i < labels.size() && !found) {
			if (std::strcmp(labels[i], tmp)) {
				++i;
			} else {
				found = true;
			}
		}
		if (found) {
			si.push_back(i);
		} else {
			throw "start point not a state!\n";
		}
		token = std::strtok(nullptr, " ");
	}

	in.getline(buffer, 256);
	token = std::strtok(buffer, " ");
	while (token != nullptr) {
		char *tmp = new char[std::strlen(token)+1];
		tmp = strcpy(tmp, token);
		int i = 0;
		bool found = false;
		while (i < labels.size() && !found) {
			if (std::strcmp(labels[i], tmp)) {
				++i;
			} else {
				found = true;
			}
		}
		if (found) {
			ei.push_back(i);
		} else {
			throw "end point not a state!\n";
		}
		token = std::strtok(nullptr, " ");
	}

	in.getline(buffer, 256);
	while (!in.eof()) {
		token = std::strtok(buffer, " ");
		
		int i = 0, sp, ep, l;
		while (i < labels.size() && std::strcmp(labels[i], token)) {
			++i;
		}
		if (i < labels.size()) {
			sp = i;
		} else {
			throw "not a state!\n";
		}
		token = std::strtok(nullptr, " ");

		i = 0;
		while (i < letters.size() && std::strcmp(letters[i], token)) {
			++i;
		}
		if (i < letters.size()) {
			l = i;
		} else {
			throw "not a letter!\n";
		}
		token = std::strtok(nullptr, " ");

		i = 0;
		while (i < labels.size() && std::strcmp(labels[i], token)) {
			++i;
		}
		if (i < labels.size()) {
			ep = i;
		} else {
			throw "not a state!\n";
		}
		token = std::strtok(nullptr, " ");

		graph[sp][ep] = l;

		in.getline(buffer, 256);
	}

	return in;
}

std::ostream &Automaton::print_test(std::ostream &out) const
{
	out << labels[si[0]];
	for (int i = 1; i < si.size(); ++i) {
		out << ", " << labels[si[i]];
	}
	out << std::endl;

	out << labels[ei[0]];
	for (int i = 1; i < ei.size(); ++i) {
		out << ", " << labels[ei[i]];
	}
	out << std::endl;

	out << labels[0];
	for (int i = 1; i < labels.size(); ++i) {
		out << std::setfill(' ') << std::setw(5) << labels[i];
	}
	out << std::endl;

	for (int i = 0; i < size; ++i) {
		int tmp = graph[i][0];
		if (tmp == -1) {
			out << "_";
		} else {
			out << letters[graph[i][0]];
		}
		for (int j = 1; j < size; ++j) {
			int tmp = graph[i][j];
			if (tmp == -1) {
				out << std::setfill(' ') << std::setw(5) << "_";
			} else {
				out << std::setfill(' ') << std::setw(5) << letters[graph[i][j]];
			}
		}
		out << std::endl;
	}

	return out;
}

std::ostream &Automaton::print(std::ostream &out) const
{
	if (labels.size()) {
		out << labels[0];
		for (int i = 1; i < labels.size(); ++i) {
			out << " " << labels[i];
		}
	}
	out << std::endl;

	if (letters.size()) {
		out << letters[0];
		for (int i = 1; i < letters.size(); ++i) {
			out << " " << letters[i];
		}
	}
	out << std::endl;

	if (si.size()) {
		out << labels[si[0]];
		for (int i = 1; i < si.size(); ++i) {
			out << " " << labels[si[i]];
		}
	}
	out << std::endl;

	if (ei.size()) {
		out << labels[ei[0]];
		for (int i = 1; i < ei.size(); ++i) {
			out << " " << labels[ei[i]];
		}
	}
	out << std::endl;

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (graph[i][j] != -1) {
				out << labels[i] << " " << letters[graph[i][j]] << " " << labels[j] << std::endl;
			}
		}
	}
	return out;
}

std::istream &operator >>(std::istream &in, Automaton &automaton)
{
	return automaton.read(in);
}

std::ostream &operator <<(std::ostream &out, const Automaton &automaton)
{
	return automaton.print(out);
}

void Automaton::exclude_unreachable()
{
	bool visited[size] = {false};

	std::stack<int> s;
	for (int i = 0; i < si.size(); ++i) {
		s.push(si[i]);
	}

	while (!s.empty()) {
		int v = s.top();
		s.pop();
		if (!visited[v]) {
			for (int i = 0; i < size; ++i) {
				if (graph[v][i] != -1) {
					s.push(i);
				}
			}
		}
		visited[v] = true;
	}

	int idx[size] = {0};
	int ns = 0;
	for (int i = 0; i < size; ++i) {
		if (visited[i]) {
			idx[i] = ns++;
		}
	}

	int **ng = new int *[ns];
	int ni = 0;
	int nj = 0;
	for (int i = 0; i < size; ++i) {
		if (visited[i]) {
			ng[ni] = new int[ns];
			nj = 0;
			for (int j = 0; j < size; ++j) {
				if (visited[j]) {
					ng[ni][nj++] = graph[i][j];
				}
			}
			++ni;
		}
	}

	bool lvs[letters.size()] = {false};
	for (int i = 0; i < ns; ++i) {
		for (int j = 0; j < ns; ++j) {
			lvs[ng[i][j]] = true;
		}
	}

	int lidx[letters.size()] = {0};
	int nls = 0;
	for (int i = 0; i < letters.size(); ++i) {
		if (lvs[i]) {
			lidx[i] = nls++;
		}
	}

	for (int i = 0; i < ns; ++i) {
		for (int j = 0; j < ns; ++j) {
			if (ng[i][j] != -1) {
				ng[i][j] = lidx[ng[i][j]];
			}
		}
	}

	std::vector<int> nsi, nei;
	std::vector<char *> nlab, nlet;
	for (int i = 0; i < si.size(); ++i) {
		if (visited[si[i]]) {
			nsi.push_back(idx[si[i]]);
		}
	}
	si = nsi;
	for (int i = 0; i < ei.size(); ++i) {
		if (visited[ei[i]]) {
			nei.push_back(idx[ei[i]]);
		}
	}
	ei = nei;
	for (int i = 0; i < size; ++i) {
		if (visited[i]) {
			char *tmp = new char[std::strlen(labels[i])+1];
			tmp = std::strcpy(tmp, labels[i]);
			nlab.push_back(tmp);
		}
		delete labels[i];
	}
	labels = nlab;
	for (int i = 0; i < letters.size(); ++i) {
		if (lvs[i]) {
			char *tmp = new char[std::strlen(letters[i])+1];
			tmp = std::strcpy(tmp, letters[i]);
			nlet.push_back(tmp);
		}
		delete letters[i];
	}
	letters = nlet;

	for (int i = 0; i < size; ++i) {
		delete graph[i];
	}
	delete graph;
	graph = ng;
	size = ns;
}

Automaton Automaton::exclude_unreachable2() const
{
	bool visited[size] = {false};

	std::stack<int> s;
	for (int i = 0; i < si.size(); ++i) {
		s.push(si[i]);
	}

	while (!s.empty()) {
		int v = s.top();
		s.pop();
		if (!visited[v]) {
			for (int i = 0; i < size; ++i) {
				if (graph[v][i] != -1) {
					s.push(i);
				}
			}
		}
		visited[v] = true;
	}

	Automaton automaton;

	int idx[size] = {0};
	for (int i = 0; i < size; ++i) {
		if (!visited[i]) {
			idx[i] = automaton.size++;
		}
	}

	automaton.graph = new int *[automaton.size];
	int ni = 0;
	int nj;
	for (int i = 0; i < size; ++i) {
		if (!visited[i]) {
			automaton.graph[ni] = new int[automaton.size];
			nj = 0;
			for (int j = 0; j < size; ++j) {
				if (!visited[j]) {
					automaton.graph[ni][nj++] = graph[i][j];
				}
			}
			++ni;
		}
	}

	bool lvs[letters.size()] = {false};
	for (int i = 0; i < automaton.size; ++i) {
		for (int j = 0; j < automaton.size; ++j) {
			lvs[automaton.graph[i][j]] = true;
		}
	}

	int lidx[letters.size()] = {0};
	int nls = 0;
	for (int i = 0; i < letters.size(); ++i) {
		if (lvs[i]) {
			lidx[i] = nls++;
		}
	}

	for (int i = 0; i < automaton.size; ++i) {
		for (int j = 0; j < automaton.size; ++j) {
			if (automaton.graph[i][j] != -1) {
				automaton.graph[i][j] = lidx[automaton.graph[i][j]];
			}
		}
	}

	for (int i = 0; i < si.size(); ++i) {
		if (!visited[si[i]]) {
			automaton.si.push_back(idx[si[i]]);
		}
	}
	for (int i = 0; i < ei.size(); ++i) {
		if (!visited[ei[i]]) {
			automaton.ei.push_back(idx[ei[i]]);
		}
	}
	for (int i = 0; i < size; ++i) {
		if (!visited[i]) {
			char *tmp = new char[std::strlen(labels[i])+1];
			tmp = std::strcpy(tmp, labels[i]);
			automaton.labels.push_back(tmp);
		}
	}
	for (int i = 0; i < letters.size(); ++i) {
		if (lvs[i]) {
			char *tmp = new char[std::strlen(letters[i])+1];
			tmp = std::strcpy(tmp, letters[i]);
			automaton.letters.push_back(tmp);
		}
	}

	return automaton;
}

void Automaton::exclude_useless()
{
	bool useful[size] = {false};
	bool visited[size] = {false};
	std::stack<int> s;
/*
	for (int i = 0; i < si.size(); ++i) {
		s.push(si[i]);
	}

	while (!s.empty()) {
		int v = s.top();
		s.pop();
		if (!visited[v]) {
			for (int i = 0; i < size; ++i) {
				if (graph[v][i] != -1) {
					s.push(i);
				}
			}
		}
		visited[v] = true;
	}
*/
	for (int i = 0; i < ei.size(); ++i) {
		s.push(ei[i]);
	}

	while (!s.empty()) {
		int v = s.top();
		s.pop();
		if (!useful[v]) {
			for (int i = 0; i < size; ++i) {
				if (graph[i][v] != -1) {
					s.push(i);
				}
			}
		}
		useful[v] = true;
	}
/*
	for (int i = 0; i < size; ++i) {
		useful[i] = useful[i] && visited[i];
	}
*/
	int idx[size] = {0};
	int ns = 0;
	for (int i = 0; i < size; ++i) {
		if (useful[i]) {
			idx[i] = ns++;
		}
	}

	int **ng = new int *[ns];
	int ni = 0;
	int nj = 0;
	for (int i = 0; i < size; ++i) {
		if (useful[i]) {
			ng[ni] = new int[ns];
			nj = 0;
			for (int j = 0; j < size; ++j) {
				if (useful[j]) {
					ng[ni][nj++] = graph[i][j];
				}
			}
			++ni;
		}
	}

	bool lvs[letters.size()] = {false};
	for (int i = 0; i < ns; ++i) {
		for (int j = 0; j < ns; ++j) {
			lvs[ng[i][j]] = true;
		}
	}

	int lidx[letters.size()] = {0};
	int nls = 0;
	for (int i = 0; i < letters.size(); ++i) {
		if (lvs[i]) {
			lidx[i] = nls++;
		}
	}

	for (int i = 0; i < ns; ++i) {
		for (int j = 0; j < ns; ++j) {
			if (ng[i][j] != -1) {
				ng[i][j] = lidx[ng[i][j]];
			}
		}
	}

	std::vector<int> nsi, nei;
	std::vector<char *> nlab, nlet;
	for (int i = 0; i < si.size(); ++i) {
		if (useful[si[i]]) {
			nsi.push_back(idx[si[i]]);
		}
	}
	si = nsi;
	for (int i = 0; i < ei.size(); ++i) {
		if (useful[ei[i]]) {
			nei.push_back(idx[ei[i]]);
		}
	}
	ei = nei;
	for (int i = 0; i < size; ++i) {
		if (useful[i]) {
			char *tmp = new char[std::strlen(labels[i])+1];
			tmp = std::strcpy(tmp, labels[i]);
			nlab.push_back(tmp);
		}
		delete labels[i];
	}
	labels = nlab;
	for (int i = 0; i < letters.size(); ++i) {
		if (lvs[i]) {
			char *tmp = new char[std::strlen(letters[i])+1];
			tmp = std::strcpy(tmp, letters[i]);
			nlet.push_back(tmp);
		}
		delete letters[i];
	}
	letters = nlet;

	for (int i = 0; i < size; ++i) {
		delete graph[i];
	}
	delete graph;
	graph = ng;
	size = ns;
}

Automaton Automaton::exclude_useless2() const
{	
	bool visited[size] = {false};

	std::stack<int> s;
	for (int i = 0; i < ei.size(); ++i) {
		s.push(ei[i]);
	}

	while (!s.empty()) {
		int v = s.top();
		s.pop();
		if (!visited[v]) {
			for (int i = 0; i < size; ++i) {
				if (graph[i][v] != -1) {
					s.push(i);
				}
			}
		}
		visited[v] = true;
	}

	Automaton automaton;

	int idx[size] = {0};
	for (int i = 0; i < size; ++i) {
		if (!visited[i]) {
			idx[i] = automaton.size++;
		}
	}

	automaton.graph = new int *[automaton.size];
	int ni = 0;
	int nj;
	for (int i = 0; i < size; ++i) {
		if (!visited[i]) {
			automaton.graph[ni] = new int[automaton.size];
			nj = 0;
			for (int j = 0; j < size; ++j) {
				if (!visited[j]) {
					automaton.graph[ni][nj++] = graph[i][j];
				}
			}
			++ni;
		}
	}

	bool lvs[letters.size()] = {false};
	for (int i = 0; i < automaton.size; ++i) {
		for (int j = 0; j < automaton.size; ++j) {
			lvs[automaton.graph[i][j]] = true;
		}
	}

	int lidx[letters.size()] = {0};
	int nls = 0;
	for (int i = 0; i < letters.size(); ++i) {
		if (lvs[i]) {
			lidx[i] = nls++;
		}
	}

	for (int i = 0; i < automaton.size; ++i) {
		for (int j = 0; j < automaton.size; ++j) {
			if (automaton.graph[i][j] != -1) {
				automaton.graph[i][j] = lidx[automaton.graph[i][j]];
			}
		}
	}

	for (int i = 0; i < si.size(); ++i) {
		if (!visited[si[i]]) {
			automaton.si.push_back(idx[si[i]]);
		}
	}
	for (int i = 0; i < ei.size(); ++i) {
		if (!visited[ei[i]]) {
			automaton.ei.push_back(idx[ei[i]]);
		}
	}
	for (int i = 0; i < size; ++i) {
		if (!visited[i]) {
			char *tmp = new char[std::strlen(labels[i])+1];
			tmp = std::strcpy(tmp, labels[i]);
			automaton.labels.push_back(tmp);
		}
	}
	for (int i = 0; i < letters.size(); ++i) {
		if (lvs[i]) {
			char *tmp = new char[std::strlen(letters[i])+1];
			tmp = std::strcpy(tmp, letters[i]);
			automaton.letters.push_back(tmp);
		}
	}

	return automaton;

}

bool Automaton::operator ==(const Automaton &oth) const
{
	if (letters.size() != oth.letters.size()) {
		return false;
	}

	for (int i = 0; i < letters.size(); ++i) {
		if (std::strcmp(letters[i], oth.letters[i])) {
			return false;
		}
	}

	bool retval = true;
	std::vector<int *> table;
	int *first = new int[(letters.size()+1)*2];
	first[0] = si[0];
	first[1] = oth.si[0];
	table.push_back(first);
	int i = 0;
	do {
		int p = table[i][0];
		int q = table[i][1];
		for (int a = 0; a < letters.size(); ++a) {
			int u = 0, v = 0, count = 0;
			while (u < labels.size() && graph[p][u] != a) {
				++u;
			}
			if (u < labels.size()) {
				table[i][(a+1)*2] = u;
				++count;
			}

			while (v < oth.labels.size() && oth.graph[q][v] != a) {
				++v;
			}
			if (v < oth.labels.size()) {
				table[i][(a+1)*2+1] = v;
				++count;
			}

			if (count == 1) {
				retfal = false;
				break;
			}

			int k = 0, l = 0;
			while (k < ei.size() && u != ei[k]) {
				++k;
			}
			while (l < oth.ei.size() && v != oth.ei[l]) {
				++l;
			}
			if ((k == ei.size() && l != oth.ei.size()) || (k != ei.size() && l == oth.ei.size())) {
				retval = false;
				break;
			}

			int j = 0;
			while (j < table.size() && (table[j][0] != u || table[j][1] != v)) {
				++j;
			}
			if (j == table.size()) {
				int *next = new int[(letters.size()+1)*2];
				next[0] = u;
				next[1] = v;
				table.push_back(next);
			}
		}
		if (!retval) {
			break;
		}
		++i;
	} while (i < table.size());

	for (i = 0; i < table.size(); ++i) {
		delete table[i];
	}

	return retval;
}

bool Automaton::recognize(const char *string) const
{
	for (int start = 0; start < si.size(); ++start) {
		if (recognize_helper(si[start], string)) {
			return true;
		}
	}
	return false;
}

bool Automaton::recognize_helper(int start, const char *string) const
{
	if (std::strlen(string) == 0) {
		int i = 0;
		while (i < ei.size() && start != ei[i]) {
			++i;
		}
		if (i < ei.size()) {
			return true;
		}
		return false;
	}

	for (int end = 0; end < size; ++end) {
		if (graph[start][end] != -1) {
			if (letters[graph[start][end]][0] == string[0]) {
				if (recognize_helper(end, string+1)) {
					return true;
				}
			}
		}
	}
	return false;
}

void Automaton::print_dot(const char *config_file) const
{
	std::ifstream config(config_file);
	std::ofstream output("automaton.gv");

	output << "digraph {" << std::endl;

	char buffer[256];
	config.getline(buffer, 256);
	do {
		output << "\t" << buffer << std::endl;
		config.getline(buffer, 256);
	} while (!config.eof());
	config.close();
	output << std::endl;

	for (auto start : si) {
		output << "\t" << "i" << labels[start] << " [shape = point, style = invis];" << std::endl;
		output << "\t" << "i" << labels[start] << " -> " << labels[start] << ";" << std::endl;
	}

	for (auto end : ei) {
		output << "\t" << labels[end] << " [shape = doublecircle];" << std::endl;
	}

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (graph[i][j] != -1) {
				output << "\t" << labels[i] << " -> " 
							   << labels[j] << " [label = " 
							   << letters[graph[i][j]] << "];" 
							   << std::endl;
			}
		}
	}

	output << "}" << std::endl;
	output.close();
}
