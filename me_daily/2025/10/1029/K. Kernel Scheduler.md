# K. Kernel Scheduler

**题目链接**: [Codeforces Gym 104785 Problem K](https://codeforces.com/gym/104785/problem/K)

## 题目理解

这是一个关于任务调度的问题。给定 n 个任务和 m 个依赖关系，每个依赖关系表示任务 ai 应该在任务 bi 之前执行。由于可能存在循环依赖，我们需要移除一些依赖关系，使得剩余的依赖关系不包含任何循环，同时保留至少 m/2 个原始依赖关系。

## 核心观察

### 1. 循环依赖的本质
- 如果存在 ai → bi 且 ai > bi，这种依赖关系更容易形成循环
- 如果存在 ai → bi 且 ai < bi，这种依赖关系符合自然顺序，不易形成循环

### 2. 贪心策略
- 将所有依赖关系分为两类：
  - **类型1**: ai > bi（逆序依赖）
  - **类型2**: ai < bi（顺序依赖）
- 选择数量更多的那一类，这样可以最大化保留的依赖关系数量

### 3. 正确性分析
- 选择同一类型的依赖关系不会产生循环
- 因为两类依赖关系的总数为 m，至少有一类的数量 ≥ m/2

## 算法思路

1. **分类统计**: 遍历所有依赖关系，根据 ai 和 bi 的大小关系分类
2. **贪心选择**: 选择数量更多的那一类依赖关系
3. **输出结果**: 输出选中的依赖关系编号

## 算法步骤

```
1. 读入 n, m
2. 初始化两个数组 idxs1, idxs2
3. for i = 1 to m:
   - 读入 ai, bi
   - if ai > bi: 将 i 加入 idxs1
   - else: 将 i 加入 idxs2
4. 选择长度更大的数组输出
```

## 多语言实现

### C++ 实现

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> idxs1, idxs2;
    
    for (int i = 1; i <= m; i++) {
        int ai, bi;
        cin >> ai >> bi;
        if (ai > bi) {
            idxs1.push_back(i);
        } else {
            idxs2.push_back(i);
        }
    }
    
    cout << "YES\n";
    
    if (idxs1.size() > idxs2.size()) {
        cout << idxs1.size() << "\n";
        for (int i = 0; i < idxs1.size(); i++) {
            cout << idxs1[i];
            if (i < idxs1.size() - 1) cout << " ";
        }
    } else {
        cout << idxs2.size() << "\n";
        for (int i = 0; i < idxs2.size(); i++) {
            cout << idxs2[i];
            if (i < idxs2.size() - 1) cout << " ";
        }
    }
    cout << "\n";
    
    return 0;
}
```


## 算法正确性分析

### 1. 为什么这样分类是正确的？
- **逆序依赖** (ai > bi): 这类依赖要求编号大的任务在编号小的任务之前执行
- **顺序依赖** (ai < bi): 这类依赖要求编号小的任务在编号小的任务之前执行
- 选择同一类型的依赖不会产生循环，因为它们都遵循相同的顺序规则

### 2. 为什么至少能保留 m/2 个依赖？
- 两类依赖的总数为 m
- 根据鸽笼原理，至少有一类的数量 ≥ ⌈m/2⌉ ≥ m/2

### 3. 贪心策略的最优性
- 我们总是选择数量更多的那一类
- 这样能最大化保留的依赖关系数量

## 复杂度分析

- **时间复杂度**: O(m)
  - 遍历所有依赖关系：O(m)
  - 输出结果：O(m)
- **空间复杂度**: O(m)
  - 存储依赖关系索引：O(m)

## 关键观察

### 1. 问题本质
- 这是一个图论中的**反馈弧集**问题的简化版本
- 通过巧妙的分类方法，将复杂的图论问题转化为简单的贪心问题
