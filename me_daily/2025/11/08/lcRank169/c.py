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

'''
替换一个元素最长非递减 a'
inc 统计最长的非严格递增数组?
🤔n 在1e5
万一有? 1 2 3 4 1 6 7 8 9这样的a。那么改a4 变 9?
dp? 改某个位置整个数组的最大非递减suba长度? 贪心?
inc 应该是无意义的 要看具体的值?
改一个pos ai应该是会拼接两部分



ex1: 1 2 3 1 2
-> 1 2 3 4 2 ans:4

ex2: 2 2 2 2 2
-> 2 2 2 2 2 ans:5

'''
n = len(a)
if n == 0:
    print(0)
    sys.exit(0)

# inc[i]: 以 i 结尾的最长非递减连续段长度
inc = [1] * n
for i in range(1, n):
    if a[i] >= a[i - 1]:
        inc[i] = inc[i - 1] + 1

# suf[i]: 以 i 开始的最长非递减连续段长度
suf = [1] * n
for i in range(n - 2, -1, -1):
    if a[i] <= a[i + 1]:
        suf[i] = suf[i + 1] + 1

# 不改的答案：原数组最长非递减子数组
ans = max(inc)

# 尝试把位置 i 改成任意值，拼接左右两段
for i in range(n):
    left = inc[i - 1] if i - 1 >= 0 else 0
    right = suf[i + 1] if i + 1 < n else 0
    # 能同时兼容左右，需要 a[i-1] <= a[i+1]
    if i - 1 >= 0 and i + 1 < n and a[i - 1] <= a[i + 1]:
        ans = max(ans, left + 1 + right)
    # 否则只能兼容一侧（选一个值让边界不破坏）
    ans = max(ans, left + 1, 1 + right)

print(ans)

