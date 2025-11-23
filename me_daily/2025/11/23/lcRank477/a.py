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
x = str(n)
new_n = int(str(n).replace('0', ''))
sum_ = 0
for c in x:
    if int(c) != 0:
        sum_ += int(c)

print(new_n * sum_)
        