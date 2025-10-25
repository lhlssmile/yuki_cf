# Arithmetics Competition

**题目来源**: Codeforces 2132E  
**难度**: 中等  
**标签**: `贪心` `三分搜索` `前缀和` `优化` `数学`

## 题目描述

在算术竞赛中，参赛者需要从他们拥有的卡片中获得尽可能高的总和。在"fst_ezik"队伍中，Vadim有n张卡片，数字为aᵢ，Kostya有m张卡片，数字为bᵢ。在q轮比赛中，他们想要获胜，但这次比赛规则与往常略有不同。

在每一轮中，参赛者会得到三个数字xᵢ、yᵢ和zᵢ。"fst_ezik"队必须从他们拥有的所有卡片中恰好选择zᵢ张卡片，但Vadim最多只能从他的集合中选择xᵢ张卡片，Kostya最多只能从他的集合中选择yᵢ张卡片。帮助他们找到每轮q轮比赛的最高可能总和。

**约束条件**:
- 1 ≤ t ≤ 10⁴（测试用例数）
- 1 ≤ n, m ≤ 2×10⁵（卡片数量）
- 1 ≤ q ≤ 10⁵（查询轮数）
- 1 ≤ aᵢ, bᵢ ≤ 10⁹（卡片数值）
- 0 ≤ xᵢ ≤ n, 0 ≤ yᵢ ≤ m, 0 ≤ zᵢ ≤ xᵢ + yᵢ

## 核心思路分析

### 问题理解与建模

1. **目标**: 在约束条件下最大化选择卡片的总和
2. **约束**: 
   - 总共必须选择恰好z张卡片
   - Vadim最多选择x张卡片
   - Kostya最多选择y张卡片
3. **关键洞察**: 这是一个在约束条件下的优化问题，可以通过枚举Vadim选择的卡片数量来解决

### 算法设计

**核心思想**: 贪心 + 三分搜索优化

1. **贪心策略**: 对两人的卡片分别按降序排序，优先选择数值最大的卡片
2. **枚举优化**: 枚举Vadim选择的卡片数量k，则Kostya选择z-k张卡片
3. **约束处理**: k的取值范围为[max(0, z-y), min(z, x)]
4. **三分搜索**: 由于目标函数可能是单峰的，使用三分搜索找到最优的k值

## C++ 代码实现详解

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<long long> solve(int n, int m, vector<long long>& va, vector<long long>& ko, 
                       const vector<array<int, 3>>& cl) {
    // 贪心策略：按降序排序，优先选择最大值
    sort(va.begin(), va.end());
    sort(ko.begin(), ko.end());
    reverse(va.begin(), va.end());
    reverse(ko.begin(), ko.end());
    
    // 计算前缀和，用于快速计算前k个元素的和
    vector<long long> prefix_va(n + 1, 0), prefix_ko(m + 1, 0);
    for (int i = 0; i < n; i++) prefix_va[i + 1] = prefix_va[i] + va[i];
    for (int i = 0; i < m; i++) prefix_ko[i + 1] = prefix_ko[i] + ko[i];
    
    vector<long long> res;
    
    for (auto& query : cl) {
        int x = query[0], y = query[1], z = query[2];
        
        // 特殊情况：不需要选择任何卡片
        if (z == 0) {
            res.push_back(0);
            continue;
        }
        
        // 计算Vadim选择卡片数量k的取值范围
        int L = max(0, z - y);      // 最少选择数量
        int R = min(z, x);          // 最多选择数量
        
        // 无解情况
        if (L > R) {
            res.push_back(0);
            continue;
        }
        
        // 目标函数：Vadim选择k张，Kostya选择z-k张
        auto func = [&](int k) -> long long {
            return prefix_va[k] + prefix_ko[z - k];
        };
        
        // 三分搜索找到最优的k值
        int low = L, high = R;
        while (high - low >= 3) {
            int m1 = low + (high - low) / 3;
            int m2 = high - (high - low) / 3;
            if (func(m1) > func(m2)) {
                high = m2;
            } else {
                low = m1;
            }
        }
        
        // 在剩余的小范围内暴力搜索最优值
        long long mx = 0;
        for (int k = low; k <= high; ++k) {
            mx = max(mx, func(k));
        }
        res.push_back(mx);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;
        
        vector<long long> a(n), b(m);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < m; i++) cin >> b[i];
        
        vector<array<int, 3>> queries(q);
        for (int i = 0; i < q; i++) {
            cin >> queries[i][0] >> queries[i][1] >> queries[i][2];
        }
        
        auto ans = solve(n, m, a, b, queries);
        for (auto v : ans) cout << v << "\n";
    }
    return 0;
}
```

### 代码关键部分解析

1. **贪心排序**:
   ```cpp
   sort(va.begin(), va.end());
   reverse(va.begin(), va.end());
   ```
   将卡片按数值降序排列，确保优先选择最大的卡片。

2. **前缀和优化**:
   ```cpp
   vector<long long> prefix_va(n + 1, 0);
   for (int i = 0; i < n; i++) prefix_va[i + 1] = prefix_va[i] + va[i];
   ```
   预计算前缀和，使得计算前k个最大元素的和的时间复杂度为O(1)。

3. **约束范围计算**:
   ```cpp
   int L = max(0, z - y);      // Vadim最少选择数量
   int R = min(z, x);          // Vadim最多选择数量
   ```
   确保选择方案满足所有约束条件。

4. **三分搜索**:
   ```cpp
   while (high - low >= 3) {
       int m1 = low + (high - low) / 3;
       int m2 = high - (high - low) / 3;
       if (func(m1) > func(m2)) {
           high = m2;
       } else {
           low = m1;
       }
   }
   ```
   利用目标函数的单峰性质，快速找到最优解。

## 复杂度分析

- **时间复杂度**: O((n + m) log(n + m) + q × log(n + m))
  - 排序：O((n + m) log(n + m))
  - 前缀和预处理：O(n + m)
  - 每个查询的三分搜索：O(log(n + m))
- **空间复杂度**: O(n + m + q)
  - 存储卡片数组、前缀和数组和查询结果

## 算法正确性证明

### 贪心策略的正确性

**引理**: 在固定选择数量的情况下，选择数值最大的卡片能获得最大总和。

**证明**: 
- 假设存在更优方案，其中选择了较小的卡片而不是较大的卡片
- 通过交换这两张卡片，总和必然增加，与假设矛盾
- 因此贪心策略是最优的

