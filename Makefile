CC		= g++
FLAGS	= -Wall -std=c++17 -fdiagnostics-color=always 2>&1

.PHONY : all clean

all : bin/automaton

bin/automaton : bin main.cpp automaton.hpp obj/automaton.o
	$(CC) -o bin/automaton main.cpp obj/automaton.o $(FLAGS)

obj/automaton.o : obj automaton.hpp automaton.cpp
	$(CC) -o obj/automaton.o -c automaton.cpp $(FLAGS)

bin	:
	mkdir bin

obj :
	mkdir obj

clean :
	-rm -rf bin obj *.out
