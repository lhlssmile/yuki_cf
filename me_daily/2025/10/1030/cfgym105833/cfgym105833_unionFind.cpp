#include <bits/stdc++.h>
using namespace std;

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
        u--, v--;  // 转为 0-indexed
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
        uf.unite(u, v);
    }
    
    // 策略1: 选择连通分量中最小的 k 条边
    vector<int> reachable_costs;
    for (auto &[u, v, w] : edges) {
        if (uf.same(u, 0)) {  // 与起点连通
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
        
        if (d > dist[u]) continue; 
        
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