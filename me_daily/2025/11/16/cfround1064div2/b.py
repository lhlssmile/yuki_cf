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
    a, b, n = LII()
    k = a // b
    print(k)
    if k == 0:
        print(1)
        continue
    if n <= k:
        print(1)
        continue
    if k == 1 and a == b:
        print(1)
        continue
    print(2)