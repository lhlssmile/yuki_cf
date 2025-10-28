import sys
from typing import List

input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

t = II()
for _ in range(t):
    n = II()
    a: List[int] = LII()
    
    parity0 = a[0] % 2
    all_same = all(x % 2 == parity0 for x in a)
    
    if all_same:
        print(' '.join(map(str, a)))
    else:
        a.sort()
        print(' '.join(map(str, a)))