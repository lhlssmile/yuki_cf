### 题目是 Codeforces Gym 105335 的 I 题（"Opposite Permutation"），讲的是给一个排列 p（大小 N），找另一个排列 q，使得 p 和 q 在所有 N! 个排列的字典序圆圈中正好对立（相隔 N!/2 位）。N 超大（到 1e6），所以代码要高效 O(N) 实现。

代码的核心是：q 的前两个元素特殊计算（基于 p 的前两个，模拟“跳过”一半排列），后 n-2 个元素则是 p 后缀的“排序配对”版本（把 p 后缀的值排序后，配对到 q 后缀的可用位置排序后）。

#### 代码整体流程
```python
from collections import defaultdict
from typing import List
import sys

input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

def main():
    n = II()
    nums = LII()  # p = [p1, p2, ..., pn]，1-based 排列

    # 计算 q 的前两个元素（ans[0] 和 ans[1]），模拟字典序“对立”偏移
    tmp = [nums[0] - 1, nums[1] - 1]
    if tmp[1] > tmp[0]:
        tmp[1] -= 1
    tmp[1] += n * (n - 1) // 2  # 加总跳跃（(n-1)! / 2 的效果）
    tmp[0] += tmp[1] // (n - 1)
    tmp[1] %= n - 1
    tmp[0] %= n
    ans = [tmp[0] + 1, tmp[1] + 1]
    if ans[1] >= ans[0]: ans[1] += 1  # 调整避免重复

    # 这里开始你问的部分：准备后缀映射
    vis1 = [0] * (n + 1)  # vis1: 标记 p 后缀（位置 2~n）中出现的值
    vis2 = [1] * (n + 1)  # vis2: 标记 q 后缀可用位置（初始全可用）

    for i in range(2, n):  # 只标记 p[2:] 的值
        vis1[nums[i]] = 1

    for x in ans:  # q 前两个用了，标记为不可用
        vis2[x] = 0

    mapping = [0] * (n + 1)  # mapping: p 后缀值 -> q 后缀对应值（排序配对）
    p1, p2 = 1, 1  # p1: 扫描 p 后缀值（从小到大），p2: 扫描 q 可用位置（从小到大）

    for _ in range(n - 2):  # 为后 n-2 个位置配对
        while not vis1[p1]: p1 += 1  # 跳过不在 p 后缀的值，找到下一个 p 后缀值
        while not vis2[p2]: p2 += 1  # 跳过已被用的 q 位置，找到下一个可用 q 值
        mapping[p1] = p2  # 配对：p 后缀的第 k 小值 -> q 后缀的第 k 小可用值
        p1 += 1
        p2 += 1

    for i in range(2, n):  # 构建 q 后缀：每个 p[i] 替换为 mapping[p[i]]
        ans.append(mapping[nums[i]])

    print(' '.join(map(str, ans)))  # 输出 q

if __name__ == "__main__":
    main()
```

#### 重点：vis1、vis2、mapping 的含义喵~
- **vis1**：一个布尔数组（大小 n+1，索引 1~n），用来**标记哪些数字出现在 p 的后缀（位置 2 到 n）中**。
  - 初始化全 0（未出现）。
  - `for i in range(2, n): vis1[nums[i]] = 1`：把 p[2:] 的每个值标记为 1（出现过）。
  - 含义：vis1[k] == 1 表示数字 k **只**在 p 的后缀中（不是 p 的前两个），这样后面扫描时能快速找到 p 后缀的“候选值列表”（本质上是 p 后缀值的“在位标记”）。
  - 为什么需要？因为 q 的后缀要基于 p 后缀“重新排序配对”，vis1 帮我们从小到大枚举 p 后缀的值（忽略前两个）。

- **vis2**：另一个布尔数组（大小 n+1），用来**标记哪些数字可用作 q 的后缀（位置 2 到 n）**。
  - 初始化全 1（全可用）。
  - `for x in ans: vis2[x] = 0`：q 前两个元素（ans[0] 和 ans[1]）已经用了，把它们标记为 0（不可用）。
  - 含义：vis2[k] == 1 表示数字 k **还能用在 q 后缀中**（没被前两个占）。这样后面能从小到大找到 q 后缀的“可用槽位”（即 q 后缀要用的数字，按从小到大顺序）。
  - 为什么需要？q 后缀的数字必须避开前两个，所以 vis2 管理“剩余可用数字”。

- **mapping**：一个数组（大小 n+1），用来**存储 p 后缀中每个值的“替换目标”在 q 后缀中**。
  - 初始化全 0（未映射）。
  - 在循环中：`mapping[p1] = p2`，其中 p1 是 p 后缀的第 k 小值（通过 vis1 扫描得到），p2 是 q 后缀的第 k 小可用值（通过 vis2 扫描得到）。
  - 含义：mapping[k] = m 表示“如果 p 的后缀里有 k，就在 q 的对应后缀位置放 m”。这是个“排序配对”：把 p 后缀的值排序（从小到大），和 q 后缀的可用值排序（从小到大），然后一一对应（zip 起来）。这样确保 q 是 p 的“对立”版本（数学上对应 factorial number system 的中点偏移）。
  - 为什么这样配对？因为在字典序圆圈中，“对立”后缀就是这种“并行排序替换”，保证总偏移是 N!/2。
