# C. No Loyalty No Royalty

**题目链接**: [Codeforces 2161 Problem C](https://codeforces.com/contest/2161/problem/C)

## 题目理解

你是一个商店的顾客，想要购买 n 个物品。每个物品 i 的价格为 ai，满足 1 ≤ ai ≤ X，其中 X 是忠诚度因子。

你在商店的忠诚度等级定义为 ⌊S/X⌋，其中 S 是到目前为止购买物品的总费用。初始时 S = 0。

如果你购买一个价格为 p 的物品，并且由于这次购买你的忠诚度等级增加了，你将获得 p 个奖励积分。

**目标**: 通过选择最优的购买顺序，找到你能获得的最大奖励积分数。

## 核心观察

### 1. 忠诚度等级机制
- 忠诚度等级 = ⌊总花费/X⌋
- 只有当购买物品后忠诚度等级**增加**时，才能获得该物品价格的奖励积分
- 关键：需要在合适的时机购买高价值物品来最大化奖励

### 2. 策略分析
- **最大可能等级**: `levels = sum(所有物品价格) / X`
- **贪心思想**: 在每个等级提升的关键时刻，购买最贵的物品来获得最大奖励
- **填充策略**: 用便宜物品填充到接近等级提升的阈值

### 3. 关键洞察
如果我们能达到 `levels` 个忠诚度等级，那么最优策略是：
- 将物品按价格降序排序
- 前 `levels` 个最贵物品用于等级提升时获得奖励
- 剩余物品用于填充，使总花费刚好达到等级提升阈值

## 算法思路

### 核心算法

```cpp
// 1. 计算最大可达等级
int levels = sum(所有物品价格) / X;

// 2. 按价格降序排序
sort(a.rbegin(), a.rend());

// 3. 前levels个物品用于获得奖励
long long bonus = sum(a[0] to a[levels-1]);

// 4. 构造购买顺序
for (int level = 0; level < levels; level++) {
    long long target = (level + 1) * X;
    // 用小物品填充到接近target
    while (cur_sum < target - a[level] && 还有小物品) {
        购买最小的物品;
    }
    // 购买大物品触发等级提升
    购买a[level];
}
```

### 算法步骤

1. **预处理**:
   - 计算所有物品总价值 `sum`
   - 计算最大可达忠诚度等级 `levels = sum / X`
   - 按价格降序排序物品

2. **分组**:
   - 前 `levels` 个最贵物品：用于等级提升时获得奖励
   - 剩余物品：用于填充到等级阈值

3. **构造购买顺序**:
   - 对于每个等级 `level` (0 到 levels-1):
     - 目标总花费：`target = (level + 1) * X`
     - 用小物品填充到 `target - a[level]`
     - 购买 `a[level]` 触发等级提升并获得奖励

4. **输出结果**:
   - 最大奖励积分：前 `levels` 个最贵物品的价格和
   - 购买顺序：按构造的顺序输出

## 完整实现

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        long long x;
        cin >> n >> x;
        
        vector<long long> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        long long sum = accumulate(a.begin(), a.end(), 0LL);
        int levels = sum / x;
        
        // 按价格降序排序
        sort(a.rbegin(), a.rend());
        
        // 计算最大奖励积分
        long long bonus = accumulate(a.begin(), a.begin() + levels, 0LL);
        
        // 分组：大物品和小物品
        vector<long long> small(a.begin() + levels, a.end());
        vector<long long> result;
        
        long long current_sum = 0;
        int large_idx = 0;
        
        // 构造购买顺序
        for (int level = 0; level < levels; level++) {
            long long target = (long long)(level + 1) * x;
            
            // 用小物品填充
            while (current_sum < target - a[large_idx] && !small.empty()) {
                long long item = small.back();
                small.pop_back();
                result.push_back(item);
                current_sum += item;
            }
            
            // 购买大物品触发等级提升
            result.push_back(a[large_idx]);
            current_sum += a[large_idx];
            large_idx++;
        }
        
        // 添加剩余小物品
        for (long long item : small) {
            result.push_back(item);
        }
        
        // 输出结果
        cout << bonus << "\n";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i];
            if (i < result.size() - 1) cout << " ";
            else cout << "\n";
        }
    }
    
    return 0;
}
```

## 算法正确性分析

### 1. 为什么贪心策略是最优的？
- **等级数固定**: 最大可达等级由总价值决定，无法改变
- **奖励最大化**: 在每次等级提升时购买最贵物品，确保奖励积分最大
- **填充最优**: 用最便宜物品填充，为购买贵物品留出空间

### 2. 构造顺序的正确性
- 确保每次购买大物品时都能触发等级提升
- 小物品的填充不会意外触发等级提升
- 最终总花费等于所有物品价格和

### 3. 边界情况处理
- `levels = 0`: 无法获得任何奖励积分
- 所有物品价格相同: 算法仍然正确
- 只有一个物品: 特殊情况，直接处理

## 复杂度分析

- **时间复杂度**: O(n log n)
  - 排序: O(n log n)
  - 构造购买顺序: O(n)
  - 总体: O(n log n)

- **空间复杂度**: O(n)
  - 存储物品数组: O(n)
  - 结果数组: O(n)

