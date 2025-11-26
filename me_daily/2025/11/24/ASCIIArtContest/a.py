from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


g, c, l = sorted(LII())

if l - g >= 10:
    print(f"check again")
else:print(f"final {c}")