from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()
#            ori ex 0011    rev ex 1100
# x ^ fx = n x=b1b2b3b4..by fx = byby-1by-2....b3b2b1
# 
t = II()
for _ in range(t):
    n = f"{II():b}"
    ans = "NO"
    for i in range(1, 64):
        if len(n) <= i:
            w = n.zfill(i)
            B = w == w[::-1]
            if i % 2 == 1:
                B = B and w[i // 2] == '0'
            if B:
                ans = "YES"
    print(ans)