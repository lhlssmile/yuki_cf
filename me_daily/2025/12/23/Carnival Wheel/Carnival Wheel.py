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
    l, a, b = LII()
    mx_score = 0
    for i in range(1,l+1):
        mx_score = max(mx_score, (a+i*b)%l)
    print(mx_score)