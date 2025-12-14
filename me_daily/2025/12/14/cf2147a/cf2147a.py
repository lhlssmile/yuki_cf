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
    x,y = LII()
    if x < y:
        print(2);continue
    elif x > y + 1 and y >= 2:
        print(3);continue
    
    print(-1)