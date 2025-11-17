from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


wl, pl = LII()

words = [SI() for _ in range(wl)]
puzzles = [SI() for _ in range(pl)]

def to_mask(s):
    m = 0
    for c in s:
        m |= 1 << (ord(c) - ord('a'))
    return m


freq = Counter()

for w in words:
    m = to_mask(w)
    if m.bit_count() <= 7: freq[m] += 1

ans = []
for p in puzzles:
    p_mask = to_mask(p)
    first_bit = 1 << (ord(p[0]) - ord('a'))
    rest = first_bit ^ p_mask

    sub = rest
    cnt = 0
    while sub:
        cnt += freq[sub | first_bit]
        sub = (sub - 1) & rest
    
    cnt += freq[first_bit]
    ans.append(cnt)
print(*ans)