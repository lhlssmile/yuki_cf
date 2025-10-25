from collections import defaultdict
from typing import List
import sys
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

t = II()
for _ in range(t):
    n, m, q = LII()
    a = LII()
    b = LII()
    queries = [LII() for _ in range(q)]
    a.sort(reverse=True)
    b.sort(reverse=True)
    prefix_a = [0] * (n + 1)
    prefix_b = [0] * (m + 1)
    for i in range(n): prefix_a[i + 1] = prefix_a[i] + a[i]
    for i in range(m): prefix_b[i + 1] = prefix_b[i] + b[i]
    for x, y, z in queries:
        if z == 0: print(0); continue
        def ternary_search(k):
            return prefix_a[k] + prefix_b[z - k]
        l, r = max(0, z - y), min(z, x)
        if l > r: print(0); continue
        lo, hi = l, r
        while hi - lo >= 3:
            m1 = lo + (hi - lo) // 3
            m2 = hi - (hi - lo) // 3
            if ternary_search(m1) > ternary_search(m2): hi = m2
            else: lo = m1
        mx = 0
        mx = max(ternary_search(i) for i in range(lo, hi + 1))
        print(mx)