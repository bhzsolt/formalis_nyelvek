#!/bin/python3

from automata import Automata

with open('input', 'r') as f:
    contents = f.read().strip()
    lines = contents.split('\n')

input_ = lines[0]

state_count = 1
stack = []
current_automata = Automata()
previous = ''
for char in input_:
    if char == '(':
        stack.append(current_automata)
        current_automata = Automata()
        current_automata.states.append(str(state_count))
        current_automata.start_state = str(state_count)
        state_count += 1
    elif char == ')':
        parent_automata = stack.pop()
        parent_automata.connect(current_automata)
        current_automata = parent_automata
    elif char == '*':
        pass 
    elif char == '|':
        pass
    else:
