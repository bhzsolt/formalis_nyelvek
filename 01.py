#!/bin/python3

from automata import Automata

automata = Automata('input')
automata.exclude_unreachable()
automata.print('unreachable')
automata.exclude_useless()
automata.print('useless')
