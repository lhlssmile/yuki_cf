from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()



s = SI()
# 每次碰到0都数数左边有几个1. ex: 1001101 1 + 3 = 4.
n = len(s)


ans = 0
i = 0
ones = 0

while i < n:
    if s[i] == '1':
        ones += 1
        i += 1
        continue
    if ones > 0:
        ans += ones
    while i < n and s[i] == '0':
        i += 1
print(ans)


