# A. Round Trip

**题目链接**: [Codeforces 2161 Problem A](https://codeforces.com/contest/2161/problem/A)

## 题目理解

你有一个初始评分 r0，想要参加 n 场比赛。每场比赛可以是 Div1 或 Div2：
- **Div1 比赛** (标记为 '1')：你总是可以参加
- **Div2 比赛** (标记为 '2')：只有当你的评分 < x 时才能参加

参加 Div2 比赛后，如果后续还有 Div2 比赛，你的评分会减少 d（但不会低于 0）。

**目标**: 计算你最多能参加多少场比赛。

## 核心观察

### 1. 比赛参与规则
- **Div1**: 无条件参加，但需要考虑评分变化的影响
- **Div2**: 需要评分 < x，参加后可能降低评分

### 2. 评分变化机制
- 只有参加 Div2 比赛**且后续还有 Div2 比赛**时，评分才会减少 d
- 评分不会降到 0 以下
- 关键：需要预判后续是否还有 Div2 比赛

### 3. 策略分析
- **贪心思想**: 能参加的比赛都要参加
- **前瞻性**: 参加 Div2 时需要考虑评分降低对后续比赛的影响
- **字符串查找**: 使用 `string::find()` 高效判断后续是否有 Div2

## 算法思路

### 核心算法

```cpp
int current_rating = r0;
int count = 0;

for (int i = 0; i < n; i++) {
    if (divs[i] == '1') {
        // Div1: 总是参加
        count++;
        // 如果后面还有Div2，评分会降低
        if (i < n-1 && divs.find('2', i+1) != string::npos) {
            current_rating = max(0, current_rating - d);
        }
    } else { // divs[i] == '2'
        if (current_rating < x) {
            // Div2: 评分足够低才能参加
            count++;
            // 如果后面还有Div2，评分会降低
            if (i < n-1 && divs.find('2', i+1) != string::npos) {
                current_rating = max(0, current_rating - d);
            }
        }
    }
}
```

### 算法步骤

1. **初始化**:
   - 当前评分 = r0
   - 参加比赛计数 = 0

2. **遍历每场比赛**:
   - **如果是 Div1 ('1')**:
     - 无条件参加，计数 +1
     - 检查后续是否有 Div2，如有则评分 -d
   
   - **如果是 Div2 ('2')**:
     - 检查当前评分是否 < x
     - 如果可以参加：计数 +1，检查后续 Div2 并可能减分
     - 如果不能参加：跳过

3. **评分更新规则**:
   - 只有参加比赛且后续还有 Div2 时才减分
   - 评分不会低于 0

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
        int r0, x, d, n;
        string divs;
        cin >> r0 >> x >> d >> n >> divs;
        
        int ans = 0;
        int cur_rating = r0;
        
        for (int i = 0; i < n; i++) {
            if (divs[i] == '1') {
                // Div1: 总是参加
                ans++;
                // 如果后面有Div2，降评分
                if (i < n - 1 && divs.find('2', i + 1) != string::npos) {
                    cur_rating = max(0, cur_rating - d);
                }
            } else { // divs[i] == '2'
                if (cur_rating < x) {
                    // Div2: 评分够低才能参加
                    ans++;
                    // 如果后面有Div2，降评分
                    if (i < n - 1 && divs.find('2', i + 1) != string::npos) {
                        cur_rating = max(0, cur_rating - d);
                    }
                }
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
```

## 算法正确性分析

### 1. 为什么贪心策略是最优的？
- **无后效性**: 每场比赛的决策只影响当前评分，不影响之前的选择
- **单调性**: 能参加的比赛越多越好，没有理由主动跳过能参加的比赛
- **评分管理**: 评分降低是被动的，我们只能通过参赛决策来应对

### 2. 评分更新的正确性
- **条件判断**: 只有参加比赛且后续有 Div2 时才减分
- **边界处理**: 评分不会低于 0
- **前瞻性**: 使用 `string::find()` 高效查找后续 Div2

### 3. 边界情况处理
- 初始评分很高：可能无法参加任何 Div2
- 初始评分很低：可以参加所有比赛
- 只有 Div1 或只有 Div2：算法仍然正确
- 评分降到 0：后续 Div2 都能参加

## 复杂度分析

- **时间复杂度**: O(n²)
  - 外层循环: O(n)
  - `string::find()`: 最坏 O(n)
  - 总体: O(n²)

- **空间复杂度**: O(1)
  - 只使用常数额外空间
  - 输入字符串不计入额外空间

