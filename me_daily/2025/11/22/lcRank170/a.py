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

def b(n):
    x = []
    while n > 0:
        if n & 1: x.append(1)
        else:x.append(0)
        n >>= 1
    return x

x = b(n)
cnt = 0
for i in range(len(x)):
    cnt += (x[i] ^ (x[len(x) - i - 1]))
print(cnt)
