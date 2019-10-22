#!/bin/python3

from automata import Automata

a1 = Automata('input')
a2 = Automata('input')

a1.exclude_unreachable
a1.exclude_useless

a2.exclude_unreachable
a2.exclude_useless

print(a1 == a2)
