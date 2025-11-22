#include <bits/stdc++.h>
using namespace std;

#define ALL(v) (v).begin(), (v).end()
#define For(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define Rof(i, n) for (int i = (n) - 1; i >= 0; --i)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); --i)
#define EACH(x, v) for (auto& x : (v))
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
using vs = vector<string>;

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
    int n, e; cin >> n >>e;
    vi ans(n), sz(n);
    V<vi> g(n);
    For(_, e) {
        int u, v;
        cin >> u >> v;g[u].pb(v), g[v].pb(u);}
    auto dfs_d = [&](this auto&& dfs_d, int u, int p, int d) -> void {
        ans[0] += d;
        sz[u] = 1;
        EACH(v, g[u]) {
            if (v != p) {
                dfs_d(v, u, d + 1);
                sz[u] += sz[v];
            }
        }
    };
    dfs_d(0, -1, 0);
    auto dfs_c = [&](this auto&& dfs_c, int u, int p, int curr_ans) -> void {
        ans[u] = curr_ans;
        EACH(v, g[u]) {
            if (v != p) {

            int new_ans = ans[u] + n - 2 * sz[v];
            dfs_c(v, u, new_ans);
            }
        }
    };
    dfs_c(0, -1, ans[0]);
    EACH(x, ans) cout << x << " ";
    return 0;
}
