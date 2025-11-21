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
    b = LII()
    S = 0
    for i in range(n):
        S ^= (a[i] ^ b[i])
    if S == 0:
        print("Tie")
        continue
    h = S.bit_length() - 1
    last = -1
    mask = 1 << h
    for i in range(n):
        if ((a[i] ^ b[i]) & mask) != 0:
            last = i + 1
    if (last & 1):
        print("Ajisai")
    else:
        print("Mai")

    