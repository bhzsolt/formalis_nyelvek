from stack import Stack
from queue import Queue

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

def to_rpn(regexp):
    regexp = expand(regexp)
    stack = Stack()
    queue = ''
    for char in regexp:
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
