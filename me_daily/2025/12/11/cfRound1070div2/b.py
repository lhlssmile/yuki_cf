import sys
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
SI = lambda: input()

t = II()
for _ in range(t):
    n = II()
    s = SI()
    pos = [i + 1 for i in range(n) if s[i] == '1']
    k = len(pos)
    if k == 0:
        print(0)
        continue
    maxg = 0
    for i in range(k - 1):
        g = pos[i + 1] - pos[i] - 1
        maxg = max(maxg, g)
    g = pos[0] + n - pos[-1] - 1
    maxg = max(maxg, g)
    print(maxg)