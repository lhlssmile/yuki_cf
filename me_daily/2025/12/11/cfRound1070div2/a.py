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
    cur_max = float('-inf')
    count = 0
    for x in a:
        if x >= cur_max:
            count += 1
            cur_max = x
    print(n - count)