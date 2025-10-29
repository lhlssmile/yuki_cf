from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

n, w, h = LII()
envs = []
for i in range(n):
    wi, hi = LII()
    # 只考虑能放下卡片的信封
    if wi > w and hi > h:
        envs.append((wi, hi, i + 1))  # 保存原始编号

if not envs:
    print(0)
else:
    # 按宽度排序
    envs.sort()
    
    # DP求最长递增子序列
    n = len(envs)
    dp = [1] * n
    parent = [-1] * n
    
    for i in range(1, n):
        for j in range(i):
            # 当前信封的宽高都要严格大于前一个
            if envs[i][0] > envs[j][0] and envs[i][1] > envs[j][1]:
                if dp[j] + 1 > dp[i]:
                    dp[i] = dp[j] + 1
                    parent[i] = j
    
    # 找到最长链的结尾
    max_len = max(dp)
    end_idx = dp.index(max_len)
    
    # 重构路径
    path = []
    idx = end_idx
    while idx != -1:
        path.append(envs[idx][2])  # 原始编号
        idx = parent[idx]
    
    path.reverse()
    
    print(max_len)
    print(*path)