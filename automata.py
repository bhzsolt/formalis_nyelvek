class Automata:
    def __init__(self, filename = None):
        self.states = set()
        self.language = set()
        self.start_states = None
        self.end_states = None
        self.edges = []
        if filename is not None:
            self.read(filename)

    def read(self, filename):
        with open(filename, 'r') as f:
            contents = f.read().strip()
        f.close()

        lines = contents.split('\n')

        self.states = set(lines[0].split(' '))
        
        for letter in lines[1].split(' '):
            self.language.add(letter)

        for a in lines[2].split(' '):
            if a not in self.states:
                raise Exception('{} not a state.'.format(a))
        self.start_states = lines[2].split(' ')
        
        for a in lines[3].split(' '):
            if a not in self.states:
                raise Exception('{} not a state.'.format(a))
        self.end_states = lines[3].split(' ')
        
        for edge in lines[4:]:
            raw = edge.split(' ')
            if raw[0] not in self.states:
                raise Exception('{} not a state.'.format(raw[0]))
            elif raw[1] not in self.language:
                raise Exception('{} not a letter.'.format(raw[1]))
            elif raw[2] not in self.states:
                raise Exception('{} not a state.'.format(raw[2]))
            self.edges.append((raw[0], raw[1], raw[2]))

    def print(self, filename):
        with open(filename, 'w') as f:

            for state in self.states:
                f.write('{} '.format(state))
            f.write('\n')
            for letter in self.language:
                f.write('{} '.format(letter))
            f.write('\n')
            for start in self.start_states:
                f.write('{} '.format(start))
            f.write('\n')
            for ends in self.end_states:
                f.write('{} '.format(ends))
            f.write('\n')
            for edge in self.edges:
                f.write('{} {} {}\n'.format(edge[0], edge[1], edge[2]))

        f.close()

    def print(self):
        for state in self.states:
            print('{} '.format(state), end='')
        print()
        for letter in self.language:
            print('{} '.format(letter), end='')
        print()
        for start in self.start_states:
            print('{} '.format(start), end='')
        print()
        for ends in self.end_states:
            print('{} '.format(ends), end='')
        print()
        for edge in self.edges:
            print('{} {} {}'.format(edge[0], edge[1], edge[2]))

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

    def elem(self, node, label):
        for (start, letter, end) in self.edges:
            if start == node and label == letter:
                return end
        return None

    def __eq__(self, other):
        if len(self.language) != len(other.language):
            return False
        if set() != (self.language-other.language):
            return False
        column = []
        column.append((self.start_states[0], other.start_states[0]))
        i = 0
        while True:
            (this, that) = column[i]
            j = 0
            for letter in self.language:
                newthis = self.elem(this, letter)
                newthat = other.elem(that, letter)
                if newthis in self.end_states and newthat not in other.end_states:
                    return False
                elif newthis not in self.end_states and newthat in other.end_states:
                    return False
                elif newthis == None and newthat != None:
                    return False
                elif newthis != None and newthat == None:
                    return False
                if ((newthis, newthat) not in column):
                    column.append((newthis, newthat))
                j += 1
            i += 1
            if i >= len(column):
                break
        return True

    def recognize(self, string):
        def recognize_helper(node, string):
            if len(string) == 0:
                if node in self.end_states:
                    return True
                else:
                    return False

            for (start, letter, end) in self.edges:
                if start == node and letter == string[0]:
                    if recognize_helper(end, string[1:]):
                        return True
            return False

        for start in self.start_states:
            if (recognize_helper(start, string)):
                return True
        return False

    def connect(self, other):
        for state in other.states:
            if state != other.start_states:
                self.states.append(state)
        self.language = self.language.union(other.language)
        for (start, letter, end) in other.edges:
            if start == other.start_states:
                self.edges.append((self.end_states, letter, end))
            else:
                self.edges.append((start, letter, end))
        self.end_states = other.end_states

    def continue(self, letter, label):
        self.language.add(letter)
        self.states.add(label)
        self.edges.append((self.end_states, letter, label))
        self.end_states = label


