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
    n, ra, ca, rb, cb = LII()

    ans = 0

    if rb > ra:
        ans = max(ans, rb)
    elif rb < ra:
        ans = max(ans, n - rb)
    if cb > ca:
        ans = max(ans, cb)
    elif cb < ca:
       ans = max(ans, n - cb)

    print(ans)

