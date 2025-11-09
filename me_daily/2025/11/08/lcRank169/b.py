from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


a = LII()

target = II()

'''
组合数学?
` target 可能没出现在a里面
主要元素: target在当前子数组中出现次数大于len(a') // 2
找到所有的a' 返回总数
给你一个整数数组 nums 和一个整数 target。

返回数组 nums 中满足 target 是主要元素的子数组的数目。

一个子数组的主要元素是指该元素在该子数组中出现的次数严格大于其长度的一半。

子数组是数组中的一段连续且非空的元素序列。©leetcode


ex1: 1 2 2 3 target = 2
ans = 5

ex2: 1 1 1 1  target = 1
ans = 10 l1 + l2 + l3 + l4 = 4 + 3 + 2 + 1?
len(a') = 4 target 出现次数大于 4 / 2

ex3: 1 2 3 target = 4 
ans = 4

滑动窗口? size = r - l + 1?
target 出现次数 > floor(size / 2) 向下取整? 什么时候向右移动r?
什么时候向右移动l?还是 emm不适合用滑动窗口


把每个元素变成 +1 (等于 target) 或 -1 (不等于 target)。
则子数组的“target是否严格多数” ⇔ 子数组的和 > 0。
统计前缀和 P，答案是对所有 j 计数之前的 i，满足 P[i] < P[j]。
用坐标压缩 + Fenwick 树计数即可，O(n log n)。
'''

n = len(a)
vals = [1 if x == target else -1 for x in a]

# 前缀和数组（长度 n+1）
pref = [0] * (n + 1)
for i in range(n):
    pref[i + 1] = pref[i] + vals[i]

# 坐标压缩
coords = sorted(set(pref))
idx_map = {v: i + 1 for i, v in enumerate(coords)}  # Fenwick 索引从1开始

size = len(coords)
bit = [0] * (size + 2)

def bit_add(i: int, delta: int = 1):
    while i <= size:
        bit[i] += delta
        i += i & -i

def bit_sum(i: int) -> int:
    s = 0
    while i > 0:
        s += bit[i]
        i -= i & -i
    return s

# 初始化加入 P[0]
bit_add(idx_map[pref[0]], 1)

ans = 0
for j in range(1, n + 1):
    idx = idx_map[pref[j]]
    # 之前所有 P[i] < P[j]
    ans += bit_sum(idx - 1)
    bit_add(idx, 1)

print(ans)
    