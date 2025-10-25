# Strange Machine

**题目来源**: Codeforces 2156B <mcreference link="https://codeforces.com/contest/2156/problem/B" index="1">1</mcreference>  
**难度**: 中等  
**标签**: `模拟` `循环` `贪心` `字符串处理` `数学`

## 题目描述

给定 n 台机器排成一个圆圈，其中 n ≤ 20。每台机器要么是 A 类型，要么是 B 类型。机器按顺时针方向从 1 到 n 编号，第 i 台机器的类型用 sᵢ 表示。每台机器接收一个整数 x 并根据其类型更新它：

- **A 类型**: 将 x 减 1。形式上，更新 x := x - 1
- **B 类型**: 将 x 替换为其值的一半（向下取整）。形式上，更新 x := ⌊x/2⌋

给定 q 个查询，每个查询包含一个整数 a。在每个查询中，你从机器 1 开始，持有整数 a。每秒钟，按顺序发生以下两个动作：

1. 当前机器根据其类型更新 a
2. 然后顺时针移动到下一台机器


## 核心思路分析

### 问题理解与建模

1. **目标**: 计算从给定值 a 开始，经过机器环处理后变为 0 所需的步数
2. **约束**: 机器按环形排列，每台机器有固定的操作类型
3. **关键洞察**: 
   - A 类型机器：线性减少（-1）
   - B 类型机器：指数减少（/2）
   - 需要模拟整个过程直到 a = 0

### 算法设计

**核心思想**: 直接模拟 + 优化处理连续 A 类型机器。

**优化策略**:
1. **特殊情况**: 如果所有机器都是 A 类型，直接返回 a
2. **连续 A 链**: 预计算每个位置开始的连续 A 类型机器长度
3. **快速跳跃**: 遇到连续 A 时，可以一次性处理多个步骤

## C++ 代码实现详解

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<long long> solve(int n, string& a, vector<int>& q) {
    // 特殊情况：所有机器都是 A 类型
    bool allA = true;
    for (char c : a) if (c == 'B') { allA = false; break; }
    
    vector<long long> res;
    res.reserve(q.size());
    
    if (allA) {
        for (int x : q) res.push_back(1LL * x);
        return res;
    }
    
    // 预计算每个位置开始的连续 A 链长度
    vector<int> chain(n, 0);
    for (int i = 0; i < n; ++i) {
        if (a[i] != 'A') continue;
        int len = 0;
        int p = i;
        while (len < n && a[p] == 'A') {
            ++len;
            p = (p + 1) % n;
        }
        chain[i] = len;
    }
    
    // 处理每个查询
    for (int qq : q) {
        long long x = qq;
        long long steps = 0;
        int pos = 0;
        
        while (x > 0) {
            if (a[pos] == 'B') {
                // B 类型机器：x /= 2
                x /= 2;
                ++steps;
                if (x == 0) break;
                pos = (pos + 1) % n;
            } else {
                // A 类型机器：利用预计算的链长度
                long long clen = chain[pos];
                if (x <= clen) {
                    // x 可以在这个 A 链中完全消耗
                    steps += x;
                    x = 0;
                    break;
                } else {
                    // x 大于链长度，跳过整个链
                    steps += clen;
                    x -= clen;
                    pos = (pos + (int)clen) % n;
                }
            }
        }
        res.push_back(steps);
    }
    return res;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        string s;
        cin >> s;
        vector<int> queries(q);
        for (int i = 0; i < q; i++) cin >> queries[i];
        
        auto ans = solve(n, s, queries);
        for (auto v : ans) cout << v << "\n";
    }
    return 0;
}
```

### 代码关键部分解析

1. **特殊情况处理**: 
   ```cpp
   if (allA) {
       for (int x : q) res.push_back(1LL * x);
       return res;
   }
   ```
   如果所有机器都是 A 类型，每步减 1，所以步数就是初始值。

2. **连续 A 链预计算**:
   ```cpp
   vector<int> chain(n, 0);
   for (int i = 0; i < n; ++i) {
       if (a[i] != 'A') continue;
       int len = 0;
       int p = i;
       while (len < n && a[p] == 'A') {
           ++len;
           p = (p + 1) % n;
       }
       chain[i] = len;
   }
   ```
   对每个 A 类型位置，计算从该位置开始的连续 A 机器数量。

3. **模拟过程**:
   ```cpp
   while (x > 0) {
       if (a[pos] == 'B') {
           x /= 2;
           ++steps;
           pos = (pos + 1) % n;
       } else {
           long long clen = chain[pos];
           if (x <= clen) {
               steps += x;
               x = 0;
           } else {
               steps += clen;
               x -= clen;
               pos = (pos + (int)clen) % n;
           }
       }
   }
   ```
   - 遇到 B 类型：直接处理一步
   - 遇到 A 类型：利用预计算的链长度快速跳跃

## 复杂度分析

- **时间复杂度**: O(n² + q × log(max_a))
  - 预处理连续 A 链：O(n²)
  - 每个查询：O(log(max_a))，因为 B 操作会快速减少 x
- **空间复杂度**: O(n + q)
  - 存储链长度数组和结果数组

## 算法正确性证明

### 连续 A 链优化的正确性

**引理**: 连续的 A 类型机器可以批量处理。

**证明**: 
- 如果从位置 i 开始有 len 个连续的 A 类型机器
- 那么经过这 len 步后，x 会减少 len，位置会移动到 (i + len) % n
- 这等价于逐步模拟 len 次 A 操作