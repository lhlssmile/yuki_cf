# 树上DP：公司股票最大利润问题

## 问题描述
给定公司员工数 \( n \)（ID 1 为 CEO），数组 `present[1..n]`（当前买入价）、`future[1..n]`（预期卖出价）、层级关系 `hierarchy`（无环树，1 为根）、预算 `budget`。

- 每人股票最多买一次。
- 若直属上司买了，则下属可半价买（\(\lfloor present[v]/2 \rfloor\)）。
- 求不超过预算的最大总利润（利润 = future - 实际买入价）。

**约束**：\(1 \leq n \leq 160\)，\(1 \leq budget \leq 160\)，价格 \(\leq 50\)。

**示例1**：n=2, present=[1,2], future=[4,3], hierarchy=[[1,2]], budget=3 → 输出5（1买满价1，得3；2半价1，得2；总成本2）。

## 解法思路：树形DP + 背包
这是一个树上0-1背包问题，折扣形成“链式依赖”（上司买 → 下属半价）。用**父视角状态**压缩：每个子树计算两种情况下的最大利润数组。

### 状态定义
- `dfs(x)` 返回 `f[2][budget+1]`：
  - `f[0][j]`：预算 \( j \) 下，**x 的父没买**（x 无折扣，满价买）的子树（x + 后代）最大利润。
  - `f[1][j]`：预算 \( j \) 下，**x 的父买了**（x 有折扣，半价买）的子树最大利润。
- 根节点（x=0，0-index）无父，用 `max(f[0])`（满价视角，包括不买根）。

### dfs 过程
1. **合并子树**（计算子树贡献 `sub_f[2][budget+1]`）：
   - 初始化：`sub_f[0/1][0] = 0`，其余 `-inf`。
   - 对每个孩子 y：
     - `fy = dfs(y)`（y 子树的两视角）。
     - 对于 k=0/1（x 买/不买对孩子的影响）：
       - 将 `fy[k]` 视为“超物品”（每个 jy 是可选体积，价值 `fy[k][jy]` ≥0 时选）。
       - 用 0-1 背包更新：后向 for j=jy to budget, `nf[j] = max(nf[j], sub_f[k][j-jy] + fy[k][jy])`。
   - 结果：`sub_f[0][j]` = x 不买，所有孩子无折扣 max；`sub_f[1][j]` = x 买，所有孩子有折扣 max。

2. **加当前节点 x**：
   - 对于 k=0/1（x 的父视角）：
     - 不买 x：`f[k][j] = sub_f[0][j]`（子树无折扣）。
     - 试买 x：cost = `present[x] // (k+1)`（k=0: 满价；k=1: 半价），prof = `future[x] - cost`。
       - 若 prof ≥0，对于 j ≥ cost：`f[k][j] = max(f[k][j], sub_f[1][j-cost] + prof)`（买 x → 给孩子折扣，用 sub_f[1]）。
   - 负利润自动避开（不更新）。

**时间复杂度**：O(n * budget²)，n=160, budget=160 → ~4e6，高效。

### 关键优化
- `-inf` 初始化，负利润 `if (res_y < 0) continue` 跳过。
- 背包后向更新，避免重复选同一子树。
- 叶子节点：sub_f 全0/-inf，f 只更新买/不买本节点。

## Python 
```python
from math import inf
fmax = lambda a, b: b if b > a else a

class Solution:
    def maxProfit(self, n: int, present: List[int], future: List[int], hierarchy: List[List[int]], budget: int) -> int:
        g = [[] for _ in range(n)]
        for x, y in hierarchy:
            g[x - 1].append(y - 1)
        def dfs(x: int) -> List[List[int]]:
            sub_f = [[0] + [-inf] * budget for _ in range(2)]
            for y in g[x]:
                fy = dfs(y)
                for k, fyk in enumerate(fy):
                    nf = [0] + [-inf] * budget
                    for jy, res_y in enumerate(fyk):
                        if res_y < 0: continue
                        for j in range(jy, budget + 1):
                            nf[j] = fmax(nf[j], sub_f[k][j - jy] + res_y)
                    sub_f[k] = nf
            f = [None] * 2
            for k in range(2):
                f[k] = sub_f[0].copy()
                cost = present[x] // (k + 1)
                for j in range(cost, budget + 1):
                    f[k][j] = fmax(f[k][j], sub_f[1][j - cost] + future[x] - cost)
            return f
        return max(dfs(0)[0])
```

## C++ 实现 0-index
```cpp
// ... (headers as before)
int solve(int n, vi& present, vi& future, V<vi>& hierarchy, int budget) {
    V<vi> g(n);
    EACH(x, hierarchy) { int u = x[0], v = x[1]; g[u].pb(v); }
    const int _inf = 1e9;
    auto dfs = [&](this auto&& dfs, int x) -> V<vi> {
        V<vi> sub_f(2, vi(budget + 1, -_inf));
        For(i, 2) sub_f[i][0] = 0;
        EACH(y, g[x]) {
            auto fy = dfs(y);
            For(k, 2) {
                vi nf(budget + 1, -_inf); nf[0] = 0;
                For(jy, budget + 1) {
                    int res_y = fy[k][jy];
                    if (res_y < 0) continue;
                    FOR(j, jy, budget + 1) {
                        if (sub_f[k][j - jy] == -_inf) continue;
                        nf[j] = max(nf[j], sub_f[k][j - jy] + res_y);
                    }
                }
                sub_f[k] = nf;
            }
        }
        V<vi> f(2, vi(budget + 1, -_inf));
        For(k, 2) {
            For(j, budget + 1) f[k][j] = sub_f[0][j];
            int cost = present[x] / (k + 1);
            int prof = future[x] - cost;
            if (prof < 0) continue;
            FOR(j, cost, budget + 1) {
                if (sub_f[1][j - cost] == -_inf) continue;
                f[k][j] = max(f[k][j], sub_f[1][j - cost] + prof);
            }
        }
        return f;
    };
    auto root_f = dfs(0);
    int ans = 0;
    For(j, budget + 1) ans = max(ans, root_f[0][j]);
    return ans;
}
// main: 读 n h budget, present(n), future(n), h 行 u v → hierarchy[i]={u-1,v-1}
```

## 验证：示例1 手推
- 节点1 (x=1, 叶)：sub_f[0/1]=[0,-inf,-inf,-inf]
  - f[0]: 不买[0,...]；买 cost=2, prof=1 → f[0][2]=0+1=1
  - f[1]: 不买[0,...]；买 cost=1, prof=2 → f[1][1]=0+2=2
- 节点0 (x=0)：合 y=1
  - sub_f[0] 加 fy[0]：jy=2 val=1 → sub_f[0][2]=1
  - sub_f[1] 加 fy[1]：jy=1 val=2 → sub_f[1][1]=2
  - f[0]: 不买 sub_f[0]；买 cost=1, prof=3 → f[0][1]= sub_f[1][0]+3=3；f[0][2]=sub_f[1][1]+3=5
- max(f[0])=5 ✓


