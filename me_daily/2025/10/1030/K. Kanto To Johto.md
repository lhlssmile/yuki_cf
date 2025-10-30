# K. Kanto To Johto

**题目链接**: [Codeforces Gym 105833 Problem K](https://codeforces.com/gym/105833/problem/K)

## 题目理解

Red 是一名宝可梦训练师，需要从站点 1 乘火车到达站点 N 进入城都地区。有 M 条双向火车线路，每条线路需要购买终身通行证才能使用。由于系统 bug，Red 最终只需要支付购买的通行证中最便宜的 K 个的费用。

**关键约束**:
- 只能在线路的两个端点购买该线路的通行证
- 每条线路的通行证只能购买一次
- 最终只需支付最便宜的 K 个通行证费用
- 保证从站点 1 可以到达站点 N

## 核心观察

### 1. 两种策略分析
- **策略1**: 如果使用 ≤ K 条边，每条边的费用都要计入答案 → 最短路问题
- **策略2**: 如果使用 > K 条边，可以购买所有可达边，只付最便宜的 K 条 → 选择问题

### 2. 关键洞察
如果最优解需要超过 K 条边，那么不如遍历整个连通分量的所有边，选择其中最便宜的 K 条，这样结果一定不会更差。

## 算法思路

### 方法一：BFS + 最短路 (原始解法)

```cpp
// 策略1: 计算最短路径总和
Dijkstra算法求从1到N的最短路径

// 策略2: BFS找所有可达边，选最小K条
BFS遍历从1开始的连通分量
收集所有可达边的权重
排序后取前K个的和

// 答案 = min(策略1, 策略2)
```

**时间复杂度**: O((N + M) log N + M log M)
**问题**: BFS 遍历图结构开销较大，容易超时

### 方法二：并查集优化 (推荐解法)

```cpp
// 使用并查集直接找到与起点连通的所有边
UnionFind uf(n);
for (auto &[u, v, w]: edges) {
    uf.merge(u, v);
}

// 收集连通分量中的所有边
vector<int> reachable_costs;
for (auto &[u, v, w]: edges) {
    if (uf.same(u, 0)) {  // 与起点连通
        reachable_costs.push_back(w);
    }
}

// 策略1: 选择最小的K条边
sort(reachable_costs.begin(), reachable_costs.end());
long long strategy1 = sum of first min(k, reachable_costs.size()) elements

// 策略2: 最短路径 (Dijkstra)
long long strategy2 = shortest_path(1, n)

// 答案 = min(strategy1, strategy2)
```

**时间复杂度**: O(M log M + (N + M) log N)
**优势**: 并查集操作比 BFS 更高效，空间局部性更好

## 完整实现

### 并查集数据结构

```cpp
struct UnionFind {
    vector<int> parent, rank;
    
    UnionFind(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x != y) {
            if (rank[x] < rank[y]) swap(x, y);
            parent[y] = x;
            if (rank[x] == rank[y]) rank[x]++;
        }
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};
```

### 主算法实现

```cpp
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<array<int, 3>> edges(m);
    vector<vector<pair<int, int>>> adj(n);
    UnionFind uf(n);
    
    for (auto &[u, v, w] : edges) {
        cin >> u >> v >> w;
        u--, v--;  // 转为0-indexed
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
        uf.unite(u, v);
    }
    
    // 策略1: 选择连通分量中最小的k条边
    vector<int> reachable_costs;
    for (auto &[u, v, w] : edges) {
        if (uf.same(u, 0)) {
            reachable_costs.push_back(w);
        }
    }
    
    sort(reachable_costs.begin(), reachable_costs.end());
    long long strategy1 = 0;
    for (int i = 0; i < min(k, (int)reachable_costs.size()); i++) {
        strategy1 += reachable_costs[i];
    }
    
    // 策略2: 最短路径
    vector<long long> dist(n, LLONG_MAX);
    dist[0] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    pq.emplace(0, 0);
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d > dist[u]) continue;  // 关键优化
        
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    
    cout << min(strategy1, dist[n-1]) << '\n';
    return 0;
}
```

## 算法正确性分析

### 1. 为什么两种策略覆盖所有情况？
- 如果最优解使用 ≤ K 条边：每条边费用都计入，等价于最短路
- 如果最优解使用 > K 条边：可以购买更多边但只付 K 条，贪心选择最便宜的

### 2. 为什么贪心策略是最优的？
- 当可以购买任意多条边时，显然应该选择最便宜的 K 条
- 连通性保证了所有选择的边都是可达的

### 3. 并查集优化的正确性
- 并查集能正确识别与起点连通的所有边
- 避免了 BFS 的图遍历开销
- 时间复杂度从 O(N + M) 优化到 O(M α(N))

## 性能对比分析

### 原始解法超时原因
1. **BFS 开销**: 需要遍历整个图结构
2. **缓存不友好**: 图遍历的内存访问模式不规律
3. **常数因子**: deque 操作比并查集数组操作慢

### 并查集优化优势
1. **直接查询**: O(α(N)) 时间判断连通性
2. **空间局部性**: 数组操作缓存友好
3. **常数优化**: 路径压缩减少重复计算

## 复杂度分析

- **时间复杂度**: O(M log M)
  - 并查集操作: O(M α(N)) ≈ O(M)
  - 排序: O(M log M)
  - Dijkstra: O((N + M) log N)
  - 总体: O(M log M + (N + M) log N)

- **空间复杂度**: O(N + M)
  - 并查集: O(N)
  - 邻接表: O(N + M)
  - 辅助数组: O(M)

## 关键优化技巧

### 1. Dijkstra 优化
```cpp
if (d > dist[u]) continue;  // 跳过过时节点
```

### 2. 0-indexed 转换
```cpp
u--, v--;  // 减少边界处理
```
