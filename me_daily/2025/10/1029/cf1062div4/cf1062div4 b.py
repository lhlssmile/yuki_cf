from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


q = II()
for _ in range(q):
    n = II()
    s, t = LSI()

    cnt_s = [0] * 26
    for c in s:
        cnt_s[ord(c) - ord('a')] += 1
    for c in t:
        cnt_s[ord(c) - ord('a')] -= 1
    if all(x == 0 for x in cnt_s):
        print("YES")
    else:
        print("NO")