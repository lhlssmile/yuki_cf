from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

t = II()
for _ in range(t):
    # 有向点权?
    m,n = LII()
    g = [[] for _ in range(n+1)]
    a = LII()
    for _ in range(m):
        u, v = LII()
        g[u].append(v)
    