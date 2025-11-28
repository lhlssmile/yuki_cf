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
    k = 0
    never_bought = []
    curr_min = float('inf')
    for i in range(n):
        if a[i] >= curr_min:
            k += 1
            never_bought.append(i+1)
        else:
            curr_min = min(a[i], curr_min)
    
    print(k)
    print(*never_bought)