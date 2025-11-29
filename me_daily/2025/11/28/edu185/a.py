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
    if n == 1:
        print(1)
    elif n == 2:
        print(9)
    elif n <= 4:
        print(4*n*n - n - 4)
    else:
        print(5*n*n - 5*n - 5)
