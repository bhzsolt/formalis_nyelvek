import automata
a = automata.from_regexp('ab*cd')
a.print('test')
with open('test', 'r') as f:
	contents = f.read().strip()
lines = contents.split('\n')
for line in lines:
	print(line)
