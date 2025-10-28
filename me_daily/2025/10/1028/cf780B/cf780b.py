from collections import defaultdict
from typing import List
import sys
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()



n = II()
x = LII()
v = LII()


lo, hi = 0.0, 2 * 10 ** 9

def possible(t):
    lmx, rmx = float('-inf'), float('inf')
    for i in range(n):
        left = x[i] - v[i] * t
        right = x[i] + v[i] *t
        lmx = max(lmx, left)
        rmx = min(rmx, right)
    return lmx <= rmx 
for _ in range(100):
    mid = lo + (hi - lo) // 2
    if possible(mid):
        hi = mid
    else:
        lo = mid
print(f"{lo:.12f}")