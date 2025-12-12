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
    odd = [x for x in a if x & 1]
    even = [x for x in a if x % 2 == 0]
    if len(odd) == 0:
        print(' '.join(['0'] * n))
        continue
    max_odd = max(odd)
    even.sort(reverse=True)
    pre = [0]
    for x in even:
        pre.append(pre[-1] + x)
    num_e = len(even)
    O_prime = len(odd) - 1
    ans = []
    for k in range(1, n + 1):
        L = max(0, k - 1 - num_e)
        max_ef = min(k - 1, num_e)
        if L % 2 == 0:
            ef = max_ef
        else:
            if max_ef - 1 < 0 or O_prime <= L:
                ef = -1
            else:
                ef = max_ef - 1
        if ef == -1:
            ans.append(0)
        else:
            ans.append(max_odd + pre[ef])
    print(' '.join(map(str, ans)))