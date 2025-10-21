from collections import defaultdict
from typing import List
import sys
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()



t = II()
for _ in range(t):
    n, m = LII()
    fsb = LII()

    inc = 0
    for i in range(1, len(fsb)):
        if fsb[i] > fsb[i - 1]: inc += 1
        else: inc = 0
    if inc == len(fsb) - 1:
        print(n - fsb[-1] + 1)
        continue
    print(1)