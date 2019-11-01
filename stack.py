class Stack:
    def __init__(self, init = None):
        self.container = []
        if init != None and isinstance(init, list):
            self.container = init

    def __str__(self):
        return str(self.container)

    def __repr__(self):
        return repr(self.container)

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

    def empty(self):
        return len(self.container) == 0
