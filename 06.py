#!/bin/python3

from stack_automata import StackAutomata

a = StackAutomata('form6')
print('\'\':\t{}'.format(a.recognize('')))
print('ab:\t{}'.format(a.recognize('ab')))
print('aabb:\t{}'.format(a.recognize('aabb')))
print('abab:\t{}'.format(a.recognize('abab')))
