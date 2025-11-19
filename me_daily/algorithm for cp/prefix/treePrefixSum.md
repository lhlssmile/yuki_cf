# 树上前缀和

## 基本想法
- 把“前缀和”的思路搬到树：从根出发沿父子关系做累加，在每个结点记录到根路径的累计值。
- 路径查询常用公式基于最近公共祖先 `lca(u,v)`。

## 点权前缀和（节点有权值）
- 定义：`sum[u] = sum[parent[u]] + w[u]`，根的 `sum[root] = w[root]`。
- 根到结点路径和：直接取 `sum[u]`。
- 任意两点路径和：`pathSum(u,v) = sum[u] + sum[v] - 2·sum[lca(u,v)] + w[lca(u,v)]`。

### 参考代码（C++）
```cpp
int n, root;
vector<vector<pair<int,int>>> g; // 邻接表（若只用点权，int 即可；pair 留给边权）
vector<int> parent, depth; 
vector<long long> sum; // 点权的前缀和
vector<int> w; // 点权

void dfs_point(int u, int p){
    parent[u] = p;
    for(auto &e: g[u]){
        int v = e.first;
        if(v == p) continue;
        depth[v] = depth[u] + 1;
        sum[v] = sum[u] + w[v];
        dfs_point(v, u);
    }
}
```

## 边权前缀和（边有权值）
- 定义：`sum[u] = sum[parent[u]] + w(parent[u], u)`，根的 `sum[root] = 0`。
- 根到结点路径和：`sum[u]`。
- 任意两点路径和：`pathSum(u,v) = sum[u] + sum[v] - 2·sum[lca(u,v)]`。

### 参考代码（C++）
```cpp
vector<long long> sEdge; // 边权的前缀和

void dfs_edge(int u, int p){
    parent[u] = p;
    for(auto &e: g[u]){
        int v = e.first, wuv = e.second;
        if(v == p) continue;
        depth[v] = depth[u] + 1;
        sEdge[v] = sEdge[u] + wuv;
        dfs_edge(v, u);
    }
}
```

## 子树和（以某结点为根的整棵子树权值总和）
- 直接 DFS 累加：`sub[u] = w[u] + Σ sub[v]`（`v` 是 `u` 的子结点）。
- Euler 序展开（`tin[u]..tout[u]`）+ 数组前缀和：把点权按 `tin` 顺序线性化，`subtreeSum(u) = pref[tout[u]] - pref[tin[u]-1]`。
- 支持子树区间操作：Euler 序可配合差分、Fenwick/Segment Tree 做子树加与查询。

### 参考代码（C++）
```cpp
vector<int> tin, tout, order; 
vector<long long> sub;
int timer = 0;

void dfs_subtree(int u, int p){
    tin[u] = ++timer; 
    sub[u] = w[u];
    order.push_back(u);
    for(auto &e: g[u]){
        int v = e.first; 
        if(v == p) continue;
        dfs_subtree(v, u);
        sub[u] += sub[v];
    }
    tout[u] = timer;
}

// 若需用前缀和查询子树：
// 建一个数组 arr[tin[u]] = w[u]，pref[i] = pref[i-1] + arr[i]，
// 则 subtreeSum(u) = pref[tout[u]] - pref[tin[u]-1]。
```

## 小提示
- 点权与边权的路径公式不同，注意 `lca` 的加项是否包含结点权。
- 需要大量路径查询时，可配合 LCA（倍增/树剖）与上述前缀和快速计算。
- 子树类问题优先考虑 Euler 序展开，把树问题转为区间问题，再用前缀和或树状数组/线段树处理。

## 常见应用
- 根到节点路径和查询：预处理 `sum[u]` 后直接取值，适合统计“从根到某点的代价”。
- 任意两点路径和查询：结合 `lca` 用公式快速求值，适合问答型路径查询。
- 子树总和与子树加：Euler 序线性化后做数组前缀和（静态），或用 Fenwick/Segment Tree（动态）。
- 路径加与路径和：用树链剖分（HLD）把路径拆成若干区间，再在区间结构上做加和查询。
- 支持批量离线：把树问题转化为序列问题，前缀和/差分能降低常数并简化实现。

## 练习链接
- LeetCode 437 Path Sum III（树上路径前缀和计数）：https://leetcode.com/problems/path-sum-iii/
- LeetCode 112 Path Sum（根到叶路径和判定）：https://leetcode.com/problems/path-sum/
- LeetCode 129 Sum Root to Leaf Numbers（根到叶累加）：https://leetcode.com/problems/sum-root-to-leaf-numbers/
- Codeforces 383C Propagating Tree（Euler 序 + 区间结构处理子树操作）：https://codeforces.com/problemset/problem/383/C
- Codeforces 600E Lomsat Gelral（子树统计，可对比 Euler 序思路）：https://codeforces.com/problemset/problem/600/E
- 洛谷 P3379【模板】最近公共祖先（LCA）：https://www.luogu.com.cn/problem/P3379
- 洛谷 P3384【模板】树链剖分（路径加/路径和）：https://www.luogu.com.cn/problem/P3384