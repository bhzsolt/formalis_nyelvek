#!/bin/python3

from automata import Automata
from automata import from_regexp
from os import system

automata = from_regexp('(0|(1(01*(00)*0)*1)*)*')
automata.print_dot(output_file='gv/output.gv', config_file='gv/config.gv')

system('dot -Txlib gv/output.gv &')
