from stack import Stack
from queue import Queue

def priority(operator):
    if operator == '+':
        return 0
    elif operator == '-':
        return 1
    elif operator in ['*', '/']:
        return 2
    return None

def to_rpn(expression):
    stack = Stack()
    queue = Queue()
    for char in expression:
        if char in ['+', '-', '*', '/']:
            if stack.top() != None:
                if priority(stack.top()) <= priority(char):
                    stack.push(char)
                else:
                    while not stack.empty() and priority(stack.top()) > priority(char):
                        queue.push(stack.pop())
                    stack.push(char)
            else:
                stack.push(char)
        else:
            queue.push(int(char))

    while not stack.empty():
        queue.push(stack.pop())

    while not queue.empty():
        tmp = queue.pop()
        if tmp in ['+', '-', '*', '/']:
            b = stack.pop()
            a = stack.pop()
            if tmp == '+':
                stack.push(a+b)
            elif tmp == '-':
                stack.push(a-b)
            elif tmp == '*':
                stack.push(a*b)
            else:
                stack.push(a/b)
        else:
            stack.push(tmp)
    print(stack.pop())
