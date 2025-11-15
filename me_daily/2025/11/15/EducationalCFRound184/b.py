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
    s = SI()
    n = len(s)
    # 判是否可无限
    infinite = False
    for i in range(n - 1):
        if s[i] != '<' and s[i + 1] != '>':
            infinite = True
            break
    if infinite:
        print(-1)
        continue

    j = s.find('*')
    if j != -1:
        print(max(j + 1, n - j))
        continue

    left = 0
    while left < n and s[left] == '<':
        left += 1
    right = 0
    while right < n and s[n - 1 - right] == '>':
        right += 1
    print(max(left, right))