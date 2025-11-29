from collections import defaultdict
from typing import List
import sys
from collections import Counter
import heapq
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


t = II()
for _ in range(t):
    n,k = LII()
    q = LII()
    r = LII()
    
    cnt_q = Counter(q)
    # 先计算所有可能的 B_a，并确定 b 的上界，仅遍历出现过的 a。
    def B_of(a: int) -> int:
        return (k - a) // (a + 1)

    usable_as = []
    maxB = -1
    for a, cnt in list(cnt_q.items()):
        if cnt <= 0:
            continue
        B = B_of(a)
        if B < 0:
            cnt_q[a] = 0
            continue
        if a == 1 and B < 1:
            cnt_q[a] = 0
            continue
        usable_as.append(a)
        if B > maxB:
            maxB = B
    B1 = B_of(1)
    dem1 = cnt_q.get(1, 0)

    # a>=2 的需求按照 B 分桶（仅遍历出现过的 a>=2）
    # 并发求 maxB 已在上面完成
    if maxB < 0:
        # 所有都不可行
        print(0)
        continue

    # r 的计数仅保留到 maxB，使用字典并按值排序
    cnt_r = Counter()
    for bval in r:
        if 0 <= bval <= maxB:
            cnt_r[bval] += 1

    # Step 1：处理 a=1（只能用 b>=1..B1），从大到小扣，保护小 b。
    ans = 0
    if dem1 > 0 and B1 >= 1:
        upper = min(B1, maxB)
        # 最大堆存放可用的 b 值（按值从大到小），结合计数字典逐个消耗
        heap_max = []
        for bval in cnt_r.keys():
            if 1 <= bval <= upper and cnt_r[bval] > 0:
                heapq.heappush(heap_max, -bval)
        while dem1 > 0 and heap_max:
            b = -heapq.heappop(heap_max)
            if cnt_r[b] == 0:
                continue
            cnt_r[b] -= 1
            ans += 1
            dem1 -= 1
            if cnt_r[b] > 0:
                heapq.heappush(heap_max, -b)

    # Step 2：处理 a>=2（可用 b>=0..B_a），按 B 从小到大，用最小 b 指针填充。
    dem_by_B = Counter()
    for a, cnt in cnt_q.items():
        if a == 1 or cnt == 0:
            continue
        B = B_of(a)
        if B >= 0:
            dem_by_B[B] += cnt

    # 预排序剩余的 b 值；用小根堆承载当前前缀内可用的 b
    vals = sorted([b for b, c in cnt_r.items() if c > 0])
    idx = 0
    heap_min = []
    for B in sorted(dem_by_B.keys()):
        # 加入所有 <= B 的 b，每个按次数压入堆
        while idx < len(vals) and vals[idx] <= B:
            b = vals[idx]
            for _ in range(cnt_r[b]):
                heapq.heappush(heap_min, b)
            idx += 1
        d = dem_by_B[B]
        while d > 0 and heap_min:
            heapq.heappop(heap_min)
            d -= 1
            ans += 1

    print(ans)


# 关系式与可行条件：
    # 选择 x,y 满足 1 <= y < x <= k，令 a=floor(x/y)，b=x%y。
    # 则 x = a*y + b 且 0 <= b <= y-1。
    # 给定 (a,b) 是否可行？存在 y 满足：y >= b+1 且 a*y + b <= k。
    # 等价于：k >= a*b + a + b，并且不是 (a=1,b=0)（该对无法满足 y<x）。
    # 这回答了：q=1,r=27,k=100 时，取 y=28 即可，x=1*28+27=55<=100。
    # 也解释了 n=3,k=10，q 中有 a=5 或 a=6 时：
    #   B_5=floor((10-5)/6)=0、B_6=floor((10-6)/7)=0，只能搭配 b=0。
    #   若 r 没有 0，则这些 q 无法被使用。
    # 多重相同值的最大化：把问题转为容量匹配：
    #   左侧顶点是 a 值（数量为其出现次数），右侧是 b 值（数量为其出现次数），
    #   边存在当且仅当 b ∈ [L_a..B_a]，其中 L_a=0(对 a>=2) 或 L_1=1，B_a=floor((k-a)/(a+1))。
    #   这些区间是“前缀”并且按 B_a 递增是嵌套的。最优贪心：
    #   1) 先把 a=1 的需求从 b 的大端（B_1->1）消耗掉，保护小 b 给更受限的 a>=2；
    #   2) 再按 B_a 从小到大处理 a>=2，始终用当前最小的 b 填充。

    # 计数 q，使用字典避免按 k 建大数组。