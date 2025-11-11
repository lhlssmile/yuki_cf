from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()



x, m, n = LII()
strs = []
for _ in range(x):
    strs.append(SI())


f = [[0] * (n + 1) for _ in range(m + 1)]

for si in strs:
    z, o = si.count('0'), si.count('1')
    for i in range(m, z - 1, -1):
        for j in range(n, o - 1, -1):
            f[i][j] = max(f[i][j], f[i - z][j - o] + 1)

print(f[m][n])