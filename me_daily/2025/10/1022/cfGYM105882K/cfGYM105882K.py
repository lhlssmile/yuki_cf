from collections import defaultdict
from typing import List
import sys
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()





n = II()

xy = []

if n & 1:
    xy.append((0, 0))
    x, y= 0, 0
    for i in range(n // 2 - 1):
        y += 25
        xy.append((x, y))
        x += 25
        xy.append((x, y))
    x = max(x, 25)
    xy.append((x, 0))
    xy.append((x // 25 * 9, x // 25 * (-12)))
else:
    xy.append((0, 0))
    x, y = 0, 0
    for i in range(n // 2 - 1):
        y += 25
        xy.append((x, y))
        x += 25
        xy.append((x, y))
    xy.append((x, 0))
dx, dy = 5, 12

for x, y in xy: print(dx * x + dy * y, (-dy) * x + dx * y)