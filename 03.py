#!/bin/python3

from automata import Automata

automata = Automata('input')
with open('words', 'r') as f:
    contents = f.read().strip()
    f.close()

with open('words_recognized', 'w') as f:

    lines = contents.split('\n')
    for word in lines:
        f.write('{}:\t{}\n'.format(word, automata.recognize(word)))
    f.close()
