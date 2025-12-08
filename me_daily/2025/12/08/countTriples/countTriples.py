from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()
import math

n = II()
MX = 251
triples = [0] * MX
def is_perfect_square(x):
    if x < 0:return False
    k = int(math.sqrt(x))
    return k * k == x
ans = 0
for a in range(1,n):
    for b in range(1,a):
        if is_perfect_square(a*a+b*b):
            ans += 1


print(ans<<1)