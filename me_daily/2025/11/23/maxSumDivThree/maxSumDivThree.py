from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

MAXV = 4 ** 10 ** 8
a = LII()
n = len(a)
INF = 10 ** 18
f = [[-INF] * 3 for _ in range(len(a) + 1)]

f[0][0] = 0

for i, x in enumerate(a):
    for j in range(3):
        f[i + 1][j] = max(f[i][j], f[i][(j + x) % 3] + x)
    
print(f[-1][0])
