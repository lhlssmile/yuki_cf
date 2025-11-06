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
'''
第ai把sword的伤害如果可以kill 第bi monster & ci > 0 将会获得一把新的拥有较大的damage(x, c)
这里的i是相同的嘛? ex:第1把🗡只能杀第1 个monster?  -> 应该不是
最多只能杀死m个monster
m 个ci
heap 存储monster&c的索引idx? 怎么排序? - 血量少得到的c越大的越好?
swords怎么存? 能不能on每次都消耗掉一把sword?如果kill不掉任意一个monster直接弹出?
单调栈？，，，不清楚

'''

t = II()

for _ in range(t):
    n, m = LII()
    swords = LII()
    b = LII()
    c = LII()
    
    monsters = sorted(zip(b, c))
    swords.sort()

    pq = []  # max-heap by c (store -c, b)
    ans = 0
    idx = 0
    
    for dmg in swords:
        while idx < m and monsters[idx][0] <= dmg:
            bi, ci = monsters[idx]
            if ci > 0:
                heapq.heappush(pq, (-ci, bi))
            else:
                ans += 1
            idx += 1
        
        if pq:
            ci, bi = heapq.heappop(pq)
            ci = -ci
            ans += 1
            dmg = max(dmg, ci)
            swords.append(dmg)
    
    print(ans)
