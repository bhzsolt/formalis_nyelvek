#!/bin/python3

from automata import Automata

a1 = Automata('input3')
a2 = Automata('input4')
a3 = Automata('input2')

print('a1 = a2: ', a1 == a2)
print('a1 = a3: ', a1 == a3)
