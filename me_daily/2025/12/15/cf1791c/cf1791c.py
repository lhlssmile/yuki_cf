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
    s = SI()
    s = list(s)
    l,r = 0,n-1
    while l <= r:
        if s[l]!=s[r]:
            l+=1
            r-=1
        else:break
    print(r-l+1)