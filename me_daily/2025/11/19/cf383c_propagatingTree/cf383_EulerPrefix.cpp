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
    int n, m; cin >> n >> m;
    vi a(n + 1); For(i, n) cin >> a[i + 1];
    V<V<int>> g(n + 1); 
    For(i, n - 1) {int u, v; cin >> u >> v; g[u].pb(v);g[v].pb(u);}
    vi in(n + 1), out(n + 1), dep(n + 1),state(n + 1, 0);
    int timer = 1;
    V<pii> st; st.reserve(2 * n); st.pb({1, 0});
    while(!st.empty()) {
        auto [u, p] = st.back(); st.pop_back();
        if (state[u] == 0) {
            state[u] = 1;
            dep[u] = (p ? dep[p] + 1 : 0);
            in[u] = timer++;
            st.pb({u, p});
            EACH(v, g[u]) if (v != p) st.pb({v, u});
        }else {
            out[u] = timer;
        }
    }
    struct BIT
    {
        int n; vll t; 
        BIT(int n) : n(n), t(n + 2, 0) {}
        void add(int i, ll v) {for (; i <= n; i += i & -i) t[i] += v;}
        ll sum(int i) {ll r = 0;for (; i > 0; i -= i & -i) r += t[i]; return r;}

    } bit(n);
    For (i, m) {
        int tp; cin >> tp; if (tp == 1) {
            int u, w; cin >> u >> w; ll s = (dep[u] % 2 == 0 ? 1 : -1);
            bit.add(in[u], w * s);
            if (out[u] <= n) bit.add(out[u], -w * s);

        }else {
            int u; cin >> u; ll s = (dep[u] % 2 == 0 ? 1 : -1);
            ll delta = bit.sum(in[u]); cout << (a[u] + s * delta) << "\n";
        }
    }
    return 0;
}