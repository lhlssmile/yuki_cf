from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()
from functools import cache

t = II()

for _ in range(t):
    n = II()
    a1 = LII()
    a2 = LII()
    # 题解引导：
    # - 路径在 2×n 上恰有一次“下”，由列 c 决定：用 top 的 [1..c] 与 bottom 的 [c..n]。
    # - 对固定 c，令 S(c) 为两段上的值集合，定义 L(c)=min S(c)，R(c)=max S(c)。
    #   连续区间 [l,r] 覆盖 S(c) ⇔ l ≤ L(c) 且 r ≥ R(c)。
    # - 固定 l，若存在 c 使 L(c) ≥ l，则让 r ≥ min_{L(c)≥l} R(c) 即可；对每个 l 累加可行 r 的个数。
    # 实现：前缀/后缀的 min/max 求 L(c)、R(c)，再按 L 做“从大到小的前缀最小值”得到 bestR(l)。

    pmn1 = [0] * n
    pmx1 = [0] * n
    pmn1[0] = a1[0]
    pmx1[0] = a1[0]
    for i in range(1, n):
        v = a1[i]
        pmn1[i] = pmn1[i - 1] if pmn1[i - 1] < v else v
        pmx1[i] = pmx1[i - 1] if pmx1[i - 1] > v else v

    smn2 = [0] * n
    smx2 = [0] * n
    smn2[n - 1] = a2[n - 1]
    smx2[n - 1] = a2[n - 1]
    for i in range(n - 2, -1, -1):
        v = a2[i]
        smn2[i] = smn2[i + 1] if smn2[i + 1] < v else v
        smx2[i] = smx2[i + 1] if smx2[i + 1] > v else v

    twoN = 2 * n
    INF = 10 ** 9
    exactR = [INF] * (twoN + 2)  # exactR[L] = 具有该 L 的最小 R
    for c in range(n):
        Lc = pmn1[c] if pmn1[c] < smn2[c] else smn2[c]
        Rc = pmx1[c] if pmx1[c] > smx2[c] else smx2[c]
        if Rc < exactR[Lc]:
            exactR[Lc] = Rc

    bestR = [INF] * (twoN + 3)   # bestR[l] = min_{L≥l} exactR[L]
    for v in range(twoN, 0, -1):
        m = exactR[v]
        tmin = bestR[v + 1]
        bestR[v] = m if m < tmin else tmin

    ans = 0
    for l in range(1, twoN + 1):
        rmin = bestR[l]
        if rmin < INF:
            ans += (twoN - rmin + 1)
    print(ans)
        
