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
    st = set(a)
    d = len(st)

    ans = d
    while ans not in st:ans+=1
    print(ans)

