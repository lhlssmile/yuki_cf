

## 📌 固定长度子数组最小逆序对 — 笔记

### ✨问题描述

给定数组 `nums`，窗口长度 `k`。  
对每个连续长度为 `k` 的子数组计算逆序对数量（i < j 且 nums[i] > nums[j]）。  
求所有窗口中逆序对数的最小值。

---

## 🔍核心思路总结

|技巧|目的|
|---|---|
|**滑动窗口**|避免每次重新统计逆序|
|**Fenwick 树（BIT）**|支持快速：插入、删除、统计多少数比当前值大/小|
|**离散化（Rank 压缩）**|Fenwick 树必须基于连续下标（不能直接用 1e9 的值当 index）|

---

## 🧩 离散化（Rank）

将 `nums` 中的值映射到排序后的排名：

```cpp
vector<int> vals = nums;
sort(vals.begin(), vals.end());
vals.erase(unique(vals.begin(), vals.end()), vals.end());

vector<int> rk(n);
for (int i = 0; i < n; ++i) {
    rk[i] = lower_bound(vals.begin(), vals.end(), nums[i]) - vals.begin() + 1;
}
```

示例：`[3,1,2,5,4] → 排序 → [1,2,3,4,5]`  
则 rank：`[3,1,2,5,4] → [3,1,2,5,4]`

👉 含义：  
rank[i] 表示 `nums[i]` 在所有出现数字的排序顺序（从 1 开始）

---

## 🌲 Fenwick 树（BIT）

### 功能

- `sum(x)`：统计所有 **rank ≤ x** 出现了多少次
    
- `range(l, r)`：统计 rank 在 `[l, r]` 范围出现次数
    

### Fenwick 数组的含义

每个节点负责：  
[ i \text{ 覆盖 } 2^r \text{长度的区间（} lowbit(i) = i&(−i) \text{）} ]

|i|二进制|lowbit(i)|负责范围|
|---|---|---|---|
|6|110|2|[5, 6]|
|8|1000|8|[1, 8]|

---

## 🔢 逆序对统计逻辑

当引入 `nums[i]`（rank = r）：

```text
贡献 = 当前窗口中所有 > r 的元素个数  
= ft.range(r+1, max_rank)
```

当元素滑出窗口（旧左端 `out` 元素 rank = ro）

```text
需要删除 小于 ro 的贡献  
= ft.range(1, ro-1)
```

---

## 🔄 滑动窗口更新公式

记当前窗口逆序数为 `cur_inv`

|操作|贡献变化|
|---|---|
|添加右侧元素 x|`cur_inv += count(> rank[x])`|
|删除左侧元素 y|`cur_inv -= count(< rank[y])`|

每步均为 `O(log n)`

---

## 📈复杂度

|操作|时间复杂度|
|---|---|
|离散化|O(n log n)|
|滑动窗口每次 Fenwick 更新|O(log n)|
|总计|**O(n log n)**|

适配 n ≤ 1e5

---

## 🧠常见疑问总结

|疑问|解答|
|---|---|
|为什么离散化？|Fenwick 树的索引必须连续且小（值可达 1e9）|
|为什么统计 `range(rank+1, m)`？|统计比当前元素大的数字个数（贡献新逆序对）|
|为什么滑出元素要减小于它的数量？|原先它与这些更小元素形成逆序，现在必须移除|
|Fenwick 树为什么自底向上跳？|跳 lowbit(i) 覆盖信息块，保证 O(log n)|

---

## 🎯一句话记忆模板

> BIT 维护窗口内每个值出现次数  
> **加新右边：数比它大 → +贡献**  
> **删左边：数比它小 → -贡献**

---
