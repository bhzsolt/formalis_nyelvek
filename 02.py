#!/bin/python3

from automata import Automata

a1 = Automata('inputs/input3')
a2 = Automata('inputs/input4')
a3 = Automata('inputs/input2')

print('a1 = a2: ', a1 == a2)
print('a1 = a3: ', a1 == a3)
