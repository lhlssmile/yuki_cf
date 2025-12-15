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
    b = SI()
    sb = list(b)
    a = ['1']
    last = int(sb[0]) + 1
    for i in range(1, n):
        bi = int(sb[i])
        if 1 + bi != last:
            a.append('1')
            last = 1 + bi
        else:
            a.append('0')
            last = bi
    print(''.join(a))
    
    