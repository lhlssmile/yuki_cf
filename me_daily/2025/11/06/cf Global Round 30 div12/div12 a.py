from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

# 让一个序列变成单个元素判断是否为x
'''

ai, ai + 1 -> replace to x (min(ai, ai +1 ), max(ai, ai + 1))
ex a = 2 7 5  -> 遍历n - 1次选择有 (2, 7), (5, 7)
最终左右区间包含x即可?让右尽量大左尽量小？
ex: -1 3 7 9 -2
'''

t = II()
for _ in range(t):
    n = II()
    a = LII()
    x = II()
    
    min_e = min(a)
    max_e = max(a)
    if min_e <= x <= max_e: print("YES")
    else: print("NO")
