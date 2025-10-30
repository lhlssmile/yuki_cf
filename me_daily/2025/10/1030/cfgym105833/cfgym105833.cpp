#include <bits/stdc++.h>
using namespace std;

#define ALL(v) (v).begin(), (v).end()
#define For(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define pb push_back
#define fi first
#define se second
#define V vector
#define SORT(v) sort(ALL(v))

using umpii = unordered_map<int, int>;
using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;

const int inf = 0x3f3f3f3f;
const ll infl = 0x3f3f3f3f3f3f3f3fll;
const int mod = 1e9 + 7;

int fastio_init = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    V<V<pii>> adj(n + 1);
    V<array<int, 3>> edges;
    For(i, m) {
        int x, y, c; cin >> x >> y >> c;
        adj[x].pb({y, c});
        adj[y].pb({x, c});
        edges.pb({x, y, c});
    }
    // Dijkstra: SP_sum from 1 to n
    vll dist(n + 1, infl);
    dist[1] = 0;
    // min-heap: greater<pii> (dist, node)
    priority_queue<pii, V<pii>, greater<pii>> pq;
    pq.emplace(0, 1);
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;  // 旧节点跳过
        for (auto& [v, c] : adj[u]) {
            if (dist[v] > dist[u] + c) {
                dist[v] = dist[u] + c;
                pq.emplace(dist[v], v);
            }
        }
    }
    ll sp_sum = dist[n];  // 策略1: SP总和

    vi vis(n + 1, false);
    vis[1] = true; 
    deque<int> q;
    q.emplace_back(1);
    while (!q.empty()) {
        auto u = q.front(); q.pop_front();
        for (auto& [v, _] : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.emplace_back(v);
            }
        }
    }

    vll cost;
    for (auto& [x, y, c] : edges) {
        if (vis[x] && vis[y]) {
            cost.pb(c);
        }
    }
    SORT(cost);
    size_t t = min(cost.size(), (size_t)k); 
    ll strat2 = accumulate(cost.begin(), cost.begin() + t, 0LL);  // 0LL init

    // ans = min(SP, K小sum)
    cout << min(sp_sum, strat2) << '\n'; 
    return 0;
}