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
    a = LII()
    b = LII()

    mink,maxk = 0, 0

    for i in range(n):
        nxtmax = max(maxk - a[i], b[i] - mink)
        nxtmin = min(mink - a[i], b[i] - maxk)
        maxk = nxtmax
        mink = nxtmin

    print(maxk)