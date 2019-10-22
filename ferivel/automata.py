from copy import copy

class Automata:
    def __init__(self):
        self.states = []
        self.language = set()
        self.end_state = None
        self.start_state = None
        self.edges = []

    def connect(self, other):
        for edge in other.edges:
            if edge[0] == other.start_state:
                self.edges.append((self.end_state, edge[1], edge[2]))
            else:
                self.edges.append(copy(edge))
        self.states += list(filter(lambda x: x != other.start_state, other.states))
        self.end_state = other.end_state
        self.language = self.language.union(other.language)
