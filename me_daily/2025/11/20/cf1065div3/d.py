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

'''
6
4
1 4 6 1
3 2 3 7
6
20 11 1 7 7 0
14 8 3 6 17 6
4
2 6 3 6
3 4 7 1
5
1 4 5 5 3
6 7 1 2 13
6
9 5 9 17 17 6
1 13 6 13 1 15
5
2 3 8 1 5
3 1 6 14 7

Mai
Ajisai
Tie
Ajisai
Mai
Tie

'''
for _ in range(t):
    n = II()
    a = LII()
    b = LII()

    S = 0
    for i in range(n):
        S ^= (a[i] ^ b[i])
    if S == 0: print("Tie"); continue
    h = S.bit_length() - 1
    mask = 1 << h
    last = -1
    for i in range(n):
        if ((a[i] ^ b[i]) & mask) != 0:
            last = i + 1
    if last & 1:
        print("Ajisai")
    else:
        print("Mai")


