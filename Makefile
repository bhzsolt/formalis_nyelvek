CC		= g++
FLAGS	= -std=c++17 -fdiagnostics-color=always 2>&1

01		= bin/labI.01
02		= bin/labI.02
03		= bin/labI.03
04		= bin/labI.04
05		= bin/labI.05
07		= bin/labI.07
main	= bin/automaton

.PHONY : all clean

all : $(01) $(02) $(03) $(05) $(07)

$(01) : bin obj $(notdir $(01)).cpp automaton.hpp obj/automaton.o
	$(CC) -o $(01) $(notdir $(01)).cpp obj/automaton.o $(FLAGS)

$(02) : bin obj $(notdir $(02)).cpp automaton.hpp obj/automaton.o
	$(CC) -o $(02) $(notdir $(02)).cpp obj/automaton.o $(FLAGS)

$(03) : bin obj $(notdir $(03)).cpp automaton.hpp obj/automaton.o
	$(CC) -o $(03) $(notdir $(03)).cpp obj/automaton.o $(FLAGS)

$(04) : bin obj $(notdir $(04)).cpp automaton.hpp obj/automaton.o
	$(CC) -o $(04) $(notdir $(04)).cpp obj/automaton.o $(FLAGS)

$(05) : bin obj $(notdir $(05)).cpp automaton.hpp obj/automaton.o
	$(CC) -o $(05) $(notdir $(05)).cpp obj/automaton.o $(FLAGS)

$(07) : bin obj $(notdir $(07)).cpp automaton.hpp regular_grammar.hpp utils.hpp obj/automaton.o obj/regular_grammar.o obj/utils.o
	$(CC) -o $(07) $(notdir $(07)).cpp obj/utils.o obj/regular_grammar.o obj/automaton.o $(FLAGS)

$(main) : bin main.cpp automaton.hpp obj/automaton.o obj/regular_grammar.o
	$(CC) -o $(main) main.cpp obj/regular_grammar.o obj/automaton.o $(FLAGS)

obj/automaton.o : obj automaton.hpp automaton.cpp
	$(CC) -o obj/automaton.o -c automaton.cpp $(FLAGS)

obj/regular_grammar.o : obj automaton.hpp regular_grammar.hpp regular_grammar.cpp
	$(CC) -o obj/regular_grammar.o -c regular_grammar.cpp $(FLAGS)

obj/utils.o : obj utils.hpp utils.cpp
	$(CC) -o obj/utils.o -c utils.cpp $(FLAGS)

bin	:
	mkdir bin

obj :
	mkdir obj

clean :
	-rm -rf bin obj *.out
