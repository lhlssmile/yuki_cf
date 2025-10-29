# Mysterious Present

## 题目链接
[Codeforces 4D](https://codeforces.com/problemset/problem/4/D)

## 题目理解

给定一张卡片的尺寸 (w, h) 和 n 个信封的尺寸 (wi, hi)。需要找到最长的信封链，使得：
1. 卡片能放入第一个信封
2. 每个信封都能放入下一个信封
3. 信封 A 能放入信封 B 当且仅当 A 的宽和高都严格小于 B 的宽和高

输出最长链的长度和对应的信封编号序列。

## 核心观察

### 关键洞察
1. **过滤条件**：只考虑能放下卡片的信封（wi > w 且 hi > h）
2. **排序策略**：按某一维度排序，简化问题为一维的最长递增子序列
3. **DP状态**：dp[i] 表示以第 i 个信封结尾的最长链长度
4. **路径重构**：使用 parent 数组记录前驱，重构最优解路径

### 问题转化
- 原问题：二维偏序关系下的最长链
- 转化后：排序 + 最长递增子序列（LIS）
- 约束条件：wi < wj 且 hi < hj（严格递增）

## 算法思路

### 排序 + 动态规划
1. **预处理**：过滤出所有能放下卡片的信封
2. **排序**：按宽度排序，确保宽度的单调性
3. **DP转移**：对于每个信封，寻找所有可以作为前驱的信封
4. **路径记录**：维护 parent 数组记录最优前驱
5. **结果重构**：从最优结尾反向构造路径

### 算法步骤
```python
# 1. 过滤有效信封
envs = []
for i in range(n):
    wi, hi = LII()
    if wi > w and hi > h:  # 能放下卡片
        envs.append((wi, hi, i + 1))  # 保存原始编号

# 2. 按宽度排序
envs.sort()

# 3. DP求最长递增子序列
n = len(envs)
dp = [1] * n  # dp[i] = 以第i个信封结尾的最长链长度
parent = [-1] * n  # parent[i] = 第i个信封的最优前驱

for i in range(1, n):
    for j in range(i):
        # 检查严格递增条件
        if envs[i][0] > envs[j][0] and envs[i][1] > envs[j][1]:
            if dp[j] + 1 > dp[i]:
                dp[i] = dp[j] + 1
                parent[i] = j

# 4. 找到最优解并重构路径
max_len = max(dp)
end_idx = dp.index(max_len)

path = []
idx = end_idx
while idx != -1:
    path.append(envs[idx][2])  # 原始编号
    idx = parent[idx]
path.reverse()
```

## 算法正确性

### 排序的必要性
- 按宽度排序后，对于 i < j，必有 wi ≤ wj
- 这样在 DP 转移时，只需检查高度的递增关系
- 避免了二维比较的复杂性

### DP状态转移正确性
- **状态定义**：dp[i] 表示以信封 i 结尾的最长链长度
- **转移方程**：dp[i] = max(dp[j] + 1)，其中 j < i 且信封 j 能放入信封 i
- **最优子结构**：最长链的子链也是最长的

### 路径重构正确性
- parent[i] 记录了状态 dp[i] 的最优来源
- 从最优结尾反向追溯，得到完整的最优路径
- 最后反转得到正确的顺序

## 复杂度分析

- **时间复杂度**：O(n²)
  - 过滤信封：O(n)
  - 排序：O(n log n)
  - DP转移：O(n²)
  - 路径重构：O(n)
  - 总体：O(n²)

- **空间复杂度**：O(n)
  - 存储信封信息：O(n)
  - DP数组和parent数组：O(n)

