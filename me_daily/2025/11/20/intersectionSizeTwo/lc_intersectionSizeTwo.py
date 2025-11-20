from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


n = II()
intervals = []

for _ in range(n):
    intervals.append(LII())


intervals.sort(key= lambda x: (x[1], -x[0]))
print(*intervals)
second_last = -1
last = -1
res = 0

for s, e in intervals:
    if s <= second_last:
        continue
    elif s > last:
        res += 2
        second_last = e - 1
        last = e
    else:
        res += 1
        second_last = last
        last = e
print(res)




