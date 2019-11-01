import sys

class Queue:
    def __init__(self, init = None):
        self.container = []
        if init != None:
            self.container = init

    def top(self):
        if len(self.container) > 0:
            return self.container[0]
        return None

    def pop(self):
        if len(self.container) > 0:
            tmp = self.container[0]
            self.container[:] = self.container[1:]
            return tmp
        return None
    
    def push(self, elem):
        self.container.append(elem)

    def __str__(self):
        return str(self.container)

    def __repr__(self):
        return repr(self.container)

class Stack:
    def __init__(self, init = None):
        self.container = []
        if init != None:
            self.container = init

    def top(self):
        if len(self.container) > 0:
            return self.container[len(self.container)-1]
        return None

    def pop(self):
        if len(self.container) > 0:
            return self.container.pop()
        return None
    
    def push(self, elem):
        self.container.append(elem)

    def __str__(self):
        return str(self.container)

    def __repr__(self):
        return repr(self.container)

def to_rpn(expression):
    stack = []
    queue = []
    for char in expression:
        sys.stdout.write(char)
    sys.stdout.write('\n')
