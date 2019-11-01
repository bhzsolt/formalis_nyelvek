#!/bin/python3

from automata import Automata

automata = Automata('inputs/input')
automata.exclude_unreachable()
automata.print('outputs/unreachable')
automata.exclude_useless()
automata.print('outputs/useless')
