from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


a = LII
'''
将所有元素变成0 的最小操作次数

'''

ans = 0
top = -1

for i, x in enumerate(a):
    while top > 0 and x < a[top]:
        top -= 1
        ans += 1
    if top < 0 or x != a[top]:
        top += 1
        a[top] = x
    

print(ans + top + (a[0] > 0))