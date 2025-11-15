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
    n, a = LII()
    v = LII()
    # 统计在 a 左侧与右侧的数量（等于 a 的球 Alice 总赢）
    less = 0
    greater = 0
    for x in v:
        if x < a:
            less += 1
        elif x > a:
            greater += 1
    if less >= greater:
        print(max(0, a - 1))
    else:
        print(a + 1)