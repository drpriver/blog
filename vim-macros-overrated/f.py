


import sys
for line in sys.stdin:
    l = line.strip()
    s = l.replace(' ', '_')
    print(f'    X({s.upper()}, {s}, {s.lower()}, "{l}") \\')
