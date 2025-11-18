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
a = LII()
def pre_handle(limit: int):
    res = [[] * (limit + 1) for _ in range(limit + 1)]
    for i in range(1, limit + 1):
        for j in range(1, limit + 1):
            if i & j == 0 and i != j:
                res[i].append(j)
    return res
'''
输出与ai兼容的aj (ai & aj == 0) aj也在a中
ai = 90 = 1011010 & aj | aj = aj
aiMAX = 4e6 4000000
MAX(ai & aj) = 0011 1111 1111 1111 1111 1111
'''
ans = [-1] * n
res = pre_handle(max(a))
st = set(x for x in a)
for i, x in enumerate(a):
    for v in res[x]:
        if v in st:
            ans[i] = v
            break

print(*ans)
