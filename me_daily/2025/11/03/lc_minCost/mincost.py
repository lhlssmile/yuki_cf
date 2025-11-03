from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


# https://leetcode.cn/problems/minimum-time-to-make-rope-colorful/description/?envType=daily-question&envId=2025-11-03


t = II()
for _ in range(t):
    colors = SI()
    needed_time = LII()

    n = len(needed_time)

    ans = 0
    i = 0

    while i < n:
        j = i + 1
        while j < n and colors[j] == colors[i]:
            j += 1
        
        if j - i > 1:

            ans += sum(needed_time[i:j]) - max(needed_time[i:j])
        i = j
    print(ans)