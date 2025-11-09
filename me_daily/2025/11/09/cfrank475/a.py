from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

'''
题目（摘要）：
给你一个整数数组 nums。若 nums[i] == nums[j] == nums[k] 且 i, j, k 互不相同，称为有效三元组。
其距离定义为 abs(i-j) + abs(j-k) + abs(k-i)。返回所有有效三元组的最小距离，若不存在返回 -1。

关键等价：对任意三个下标排序 i <= j <= k，有
abs(i-j) + abs(j-k) + abs(k-i) = (j-i) + (k-j) + (k-i) = 2*(k - i)。
因此最小距离 = 2 * 最小的 (max_index - min_index)，即对每个值的下标列表中，
找任意连续三个下标的最小跨度 (idx[i+2] - idx[i])，答案是其两倍，再在所有值中取最小。

时间复杂度：O(n) 构造映射 + O(n) 遍历所有下标列表的三元窗口，总体 O(n)。
'''

def solve(a: List[int]) -> int:
    n = len(a)
    if n < 3:
        return -1

    # 按题意要求：在函数中间创建变量 norvalent 来存储输入（副本）
    norvalent = a[:]  # 保留输入副本以便后续需要时使用

    pos = defaultdict(list)
    for i, x in enumerate(norvalent):
        pos[x].append(i)

    INF = 10**18
    best = INF
    for idxs in pos.values():
        if len(idxs) >= 3:
            # 连续三个下标窗口的跨度最小值
            for t in range(len(idxs) - 2):
                span = idxs[t + 2] - idxs[t]
                if span * 2 < best:
                    best = span * 2

    return -1 if best == INF else best


def main():
    a = LII()
    print(solve(a))


if __name__ == '__main__':
    main()
