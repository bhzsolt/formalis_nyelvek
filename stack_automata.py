from copy import copy

class StackAutomata:
    def __init__(self, filename = None):
        self.states = set()
        self.language = set()
        self.stack_language = set()
        self.start_state = None
        self.stack_start = None
        self.end_states = set()
        self.edges = []
        if filename is not None:
            self.read(filename)

    def read(self, filename):
        with open(filename, 'r') as f:
            contents = f.read().strip()
        f.close()

        lines = contents.split('\n')

        self.states = set(lines[0].split(' '))
        self.language = set(lines[1].split(' '))
        self.language.add('eps')
        self.stack_language = set(lines[2].split(' '))
        self.stack_language.add('eps')

        for a in lines[3].split(' '):
            if a not in self.states:
                raise Exception('{} not a state.'.format(a))
        self.start_state = lines[3].split(' ')[0]
        
        for a in lines[4].split(' '):
            if a not in self.stack_language:
                raise Exception('{} not part of the stack language.'.format(a))
        self.stack_start = lines[4].split(' ')[0]

        for a in lines[5].split(' '):
            if a not in self.states:
                raise Exception('{} not a state.'.format(a))
            self.end_states.add(a)
        
        for edge in lines[6:]:
            raw = edge.split(' ')
            last = len(raw)-1
            if raw[0] not in self.states:
                raise Exception('{} not a state.'.format(raw[0]))
            elif raw[1] not in self.language:
                raise Exception('{} not a letter.'.format(raw[1]))
            elif raw[last] not in self.states:
                raise Exception('{} not a state.'.format(raw[last]))
            self.edges.append((raw[0], raw[1], raw[2], raw[3:last], raw[last]))

    def print(self, filename = None):
        if filename is not None:
            with open(filename, 'w') as f:
                for state in self.states:
                    f.write('{} '.format(state))
                f.write('\n')
                for letter in self.language:
                    f.write('{} '.format(letter))
                f.write('\n')
                for letter in self.stack_language:
                    f.write('{} '.format(letter))
                f.write('\n')
                f.write('{}\n'.format(self.start_state))
                f.write('{}\n'.format(self.stack_start))
                for ends in self.end_states:
                    f.write('{} '.format(ends))
                f.write('\n')
                for edge in self.edges:
                    f.write('{} {} {} '.format(edge[0], edge[1], edge[2]))
                    for stack_state in edge[3]:
                        f.write('{} '.format(stack_state))
                    f.write('{}\n'.format(edge[4]))
            f.close()
        else:
            for state in self.states:
                print('{} '.format(state), end='')
            print()
            for letter in self.language:
                print('{} '.format(letter), end='')
            print()
            for letter in self.stack_language:
                print('{} '.format(letter), end='')
            print()
            print('{}'.format(self.start_state))
            print('{}'.format(self.stack_start))
            for ends in self.end_states:
                print('{} '.format(ends), end='')
            print()
            for edge in self.edges:
                print('{} {} {} '.format(edge[0], edge[1], edge[2]), end='')
                for stack_state in edge[3]:
                    print('{} '.format(stack_state), end='')
                print('{}'.format(edge[4]))

    def exclude_unreachable(self):
        stack = []
        reached = set()
        for start in self.start_states:
            stack.append(start)

        while stack != []:
            node = stack.pop()
            if node not in reached:
                reached.add(node)
                for (start, letter, end) in self.edges:
                    if start == node:
                        stack.append(end)

        state_set = set(self.states)
        not_reached = state_set - reached

        for node in not_reached:
            self.states.remove(node)
            if (node in self.end_states):
                self.end_states.remove(node)

        for (start, letter, end) in self.edges:
            if start in not_reached or end in not_reached:
                self.edges.remove((start, letter, end))

    def exclude_useless(self):
        stack = []
        reached = set()
        for end in self.end_states:
            stack.append(end)

        while stack != []:
            node = stack.pop()
            if node not in reached:
                reached.add(node)
                for (start, letter, end) in self.edges:
                    if end == node:
                        stack.append(start)

        state_set = set(self.states)
        not_reached = state_set - reached

        for node in not_reached:
            self.states.remove(node)
            if (node in self.end_states):
                self.end_states.remove(node)

        for (start, letter, end) in self.edges:
            if start in not_reached or end in not_reached:
                self.edges.remove((start, letter, end))

    def recognize(self, string):
        def recognize_helper(node, stack, string, depth):
            if len(string) == 0 and depth != 0:
                if node in self.end_states or len(stack) == 0:
                    return True
                else:
                    return False

            for (start, letter, popsymbol, pushsymbols, end) in self.edges:
                if start == node:
                    if len(stack) != 0:
                        if letter == 'eps' and stack[len(stack)-1] == popsymbol:
                            stack.pop()
                            for symbol in pushsymbols:
                                if symbol != 'eps':
                                    stack.append(symbol)
                            if recognize_helper(end, stack, string, depth+1):
                                return True
                        elif len(string) != 0 and letter == string[0] and stack[len(stack)-1] == popsymbol:
                            stack.pop()
                            for symbol in pushsymbols:
                                if symbol != 'eps':
                                    stack.append(symbol)
                            if recognize_helper(end, stack, string[1:], depth+1):
                                return True
            return False

        stack = [self.stack_start]
        if recognize_helper(self.start_state, stack, string, 0):
            return True
        return False
