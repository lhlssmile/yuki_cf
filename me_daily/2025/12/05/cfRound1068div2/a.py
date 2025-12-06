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
    # 最多睡几节课
    n, k = LII()
    s = SI()
    cnt = 0
    awake_until = -1
    for i, c in enumerate(s):
        if c == '1':
            if i + k > awake_until:
                awake_until = i + k
        else:
            if i > awake_until:
                cnt += 1
    print(cnt)
