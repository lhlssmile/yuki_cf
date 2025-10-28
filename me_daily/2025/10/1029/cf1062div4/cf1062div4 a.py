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
    st = set()
    a, b, c, d = LII()
    if a == b == c == d:
        print("YES")
    else: print("NO")