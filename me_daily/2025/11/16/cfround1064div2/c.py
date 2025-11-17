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
    n = II()
    a = [0] + LII()     # 1-based
    wsum = 0
    wmax = 0
    for i in range(1, n):
        w = max(a[i], a[i+1])
        wsum += w
        if w > wmax:
            wmax = w
    w = max(a[n], a[1])
    wsum += w
    if w > wmax:
        wmax = w
    print(wsum - wmax)
    
