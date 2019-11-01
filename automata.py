from stack import Stack

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

        self.states = set(lines[0].strip().split(' '))
        
        for letter in lines[1].strip().split(' '):
            self.language.add(letter)

        for a in lines[2].strip().split(' '):
            if a not in self.states:
                raise Exception('{} not a state.'.format(a))
        self.start_states = lines[2].split(' ')
        
        for a in lines[3].strip().split(' '):
            if a not in self.states:
                raise Exception('{} not a state.'.format(a))
        self.end_states = lines[3].strip().split(' ')
        
        for edge in lines[4:]:
            raw = edge.strip().split(' ')
            if raw[0] not in self.states:
                raise Exception('{} not a state.'.format(raw[0]))
            elif raw[1] not in self.language:
                raise Exception('{} not a letter.'.format(raw[1]))
            elif raw[2] not in self.states:
                raise Exception('{} not a state.'.format(raw[2]))
            self.edges.append((raw[0], raw[1], raw[2]))

    def print(self, filename = None):
        if filename is not None:
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
        else:
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

    def print_dot(self, output_file = 'output.gv', config_file = 'config.gv'):
        with open(config_file, 'r') as conf:
            config = conf.read().strip()
            lines = config.split('\n')
            conf.close()
        with open(output_file, 'w') as out:
            out.write('digraph {\n')
            for line in lines:
                out.write('\t')
                out.write(line)
                out.write('\n')
            out.write('\n')
            for start in self.start_states:
                out.write('\ti{} [shape = point, style = invis];\n'.format(start))
                out.write('\ti{} -> {};\n'.format(start, start))
            for end in self.end_states:
                out.write('\t{} [shape = doublecircle];\n'.format(end))
            for edge in self.edges:
                out.write('\t{} -> {} [label = {}];\n'.format(edge[0], edge[2], edge[1]))
            out.write('}\n')
            out.close()

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
        self.exclude_useless()
        self.exclude_unreachable()
        other.exclude_useless()
        other.exclude_unreachable()
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
        def eps_helper(node):
            for (start, letter, end) in self.edges:
                if start == node and letter == 'eps':
                    if end in self.end_states:
                        return True
                    else:
                        return eps_helper(end)
            return False

        def recognize_helper(node, string):
            if len(string) == 0:
                if node in self.end_states:
                    return True
                else:
                    return eps_helper(node)

            for (start, letter, end) in self.edges:
                if start == node:
                    if letter == 'eps':
                        if recognize_helper(end, string):
                            return True
                    elif letter == string[0]:
                        if recognize_helper(end, string[1:]):
                            return True
            return False

        for start in self.start_states:
            if (recognize_helper(start, string)):
                return True
        return False

    def epsilon_free(self):
        def eps_helper(node, nodes):
            for (start, letter, end) in self.edges:
                if start == node and letter == 'eps':
                    if end in self.end_states:
                        nodes.add(end)
                        return nodes
                    else:
                        nodes.add(end)
                        return eps_helper(end, nodes)
            return nodes

        def eps_delta(node):
            nodes = set()
            nodes.add(node)
            nodes = nodes.union(eps_helper(node, nodes))
            return nodes

        def letter_delta(nodes, letter):
            delta_set = set()
            for node in nodes:
                for (start, _letter, end) in self.edges:
                    if start == node and letter == _letter:
                        delta_set.add(end)
            return delta_set

        def eps_delta_set(node_set):
            nodes = set()
            nodes = nodes.union(node_set)
            for node in node_set:
                nodes = nodes.union(eps_helper(node, nodes))
            return nodes

        self.language.remove('eps')
        new_edges = []
        for start in self.states:
            for letter in self.language:
                for end in eps_delta_set(letter_delta(eps_delta(start), letter)):
                    new_edges.append((start, letter, end))
        self.edges = new_edges
    
def from_regexp(regexp):
    def inc_label(label):
        return chr(ord(label)+1)

    def priority(operator):
        if operator in ['(', ')']:
            return 0
        elif operator == '|':
            return 1
        elif operator == '.':
            return 2
        return None

    def expand(string):
        expanded = ''
        idx = 0
        while idx < len(string)-1:
            this = string[idx]
            that = string[idx+1]
            expanded += this
            if this not in ['(', '|']:
                if that not in ['*', '|', ')']:
                    expanded += '.'
            idx += 1
        expanded += that
        return expanded

    def to_rpn(string):
        string = expand(string)
        stack = Stack()
        queue = ''
        for char in string:
            if char in ['.', '|']:
                if stack.top() != None:
                    if priority(stack.top()) <= priority(char):
                        stack.push(char)
                    else:
                        while not stack.empty() and priority(stack.top()) > priority(char):
                            queue += stack.pop()
                        stack.push(char)
                else:
                    stack.push(char)
            elif char == '(':
                stack.push(char)
            elif char == ')':
                while not stack.empty() and stack.top() != '(':
                    queue += stack.pop()
                if not stack.empty():
                    stack.pop()
            else:
                queue += char
        while not stack.empty():
            queue += stack.pop()
        return queue

    def single(label, letter):
        tmp = Automata()
        tmp.states.add(label+'1')
        tmp.states.add(label+'2')
        tmp.language.add(letter)
        tmp.start_states = [label+'1']
        tmp.end_states = [label+'2']
        tmp.edges.append((label+'1', letter, label+'2'))
        return tmp

    def concat(this, that):
        tmp = Automata()
        tmp.states = this.states.union(that.states)
        tmp.language = this.language.union(that.language)
        tmp.language.add('eps')
        tmp.start_states = this.start_states
        tmp.end_states = that.end_states
        tmp.edges = this.edges + that.edges
        for start in that.start_states:
            for end in this.end_states:
                tmp.edges.append((end, 'eps', start))
        return tmp

    def union(label, this, that):
        tmp = Automata()
        tmp.states = this.states.union(that.states)
        tmp.states.add(label+'1')
        tmp.states.add(label+'2')
        tmp.language = this.language.union(that.language)
        tmp.language.add('eps')
        tmp.start_states = [label+'1']
        tmp.end_states = [label+'2']
        tmp.edges = this.edges + that.edges
        for start in this.start_states:
            tmp.edges.append((label+'1', 'eps', start))
        for start in that.start_states:
            tmp.edges.append((label+'1', 'eps', start))
        for end in this.end_states:
            tmp.edges.append((end, 'eps', label+'2'))
        for end in that.end_states:
            tmp.edges.append((end, 'eps', label+'2'))
        return tmp

    def kleene_star(label, this):
        tmp = Automata()
        tmp.states = this.states
        tmp.states.add(label+'1')
        tmp.states.add(label+'2')
        tmp.language = this.language
        tmp.language.add('eps')
        tmp.start_states = [label+'1']
        tmp.end_states = [label+'2']
        tmp.edges = this.edges
        for start in this.start_states:
            tmp.edges.append((label+'1', 'eps', start))
        for end in this.end_states:
            tmp.edges.append((end, 'eps', label+'2'))
        for start in this.start_states:
            for end in this.end_states:
                tmp.edges.append((end, 'eps', start))
        tmp.edges.append((label+'1', 'eps', label+'2'))
        return tmp

    label = 'a'
    stack = Stack()
    rpn = to_rpn(regexp)
    for char in rpn:
        if char == '*':
            tmp = stack.pop()
            stack.push(kleene_star(label, tmp))
        elif char == '|':
            b = stack.pop()
            a = stack.pop()
            stack.push(union(label, a, b))
        elif char == '.':
            b = stack.pop()
            a = stack.pop()
            stack.push(concat(a, b))
        else:
            stack.push(single(label, char))
        label = inc_label(label)
    return stack.pop()

def from_regular_grammar(grammar = 'grammar.input'):

