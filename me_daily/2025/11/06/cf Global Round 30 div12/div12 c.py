from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()
import heapq

t = II()
for _ in range(t):
    n, m = LII()
    swords = LII()
    b = LII()
    c = LII()

    monsters = sorted(zip(b, c)) 
    heapq.heapify(swords)         

    pq = []  # 候选怪的最大堆（存 -c）
    idx = 0
    ans = 0

    while swords:
        s = heapq.heappop(swords)

        # 解锁所有当前可杀的怪到候选堆
        while idx < m and monsters[idx][0] <= s:
            _, ci = monsters[idx]
            heapq.heappush(pq, -ci)
            idx += 1

        if not pq:
            # 这把剑杀不了任何已解锁的怪
            continue

        ci = -heapq.heappop(pq)
        ans += 1
        if ci > 0:
            heapq.heappush(swords, max(s, ci))

    print(ans)